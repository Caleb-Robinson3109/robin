#include <vector>

#include "token.hpp"
#include "ast.hpp"
#include "parser.hpp"

using namespace std;

AST parser (vector<Token>& tokens){
    int index = 0;
    Ret parsed = parse_Program(tokens, index);

    if(parsed.valid){
        return parsed.ast;
    }
    else{
        Node error("error", Token(), false);
        return AST(error);
    }
}

Ret parse_Program(vector<Token>& tokens, int index){
    Ret parsed_Main = parse_Main(tokens, index);
    if(parsed_Main.valid){
        return parsed_Main;
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_Main(vector<Token>& tokens, int index){
    AST Main(Node("Main", Token(), false));
    Ret parsed_MainDef = parse_MainDef(tokens, index);
    
    if(parsed_MainDef.valid){
        Ret parsed_FuncBody = parse_FuncBody(tokens, parsed_MainDef.index);
        Main.getRoot().addChild(parsed_MainDef.ast);

        if(parsed_FuncBody.valid){
            Main.getRoot().addChild(parsed_FuncBody.ast);
            return Ret(true, Main.getRoot(), parsed_FuncBody.index);
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_MainDef(vector<Token>& tokens, int index){
    AST MainDef(Node("MainDef", Token(), false));
    if(tokens.at(index).type == "kw_main"){
        MainDef.getRoot().addChild(Node("kw_main", tokens.at(index), true));
        index++;
        if(tokens.at(index).type == "kw_arrow"){
            MainDef.getRoot().addChild(Node("kw_arrow", tokens.at(index), true));
            index++;
            if(tokens.at(index).type == "kw_int"){
                MainDef.getRoot().addChild(Node("kw_int", tokens.at(index), true));
                index++;
                Ret okay(true, MainDef.getRoot(), index);
                return okay;
            }
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_FuncBody(vector<Token>& tokens, int index){
    AST FuncBody(Node("FuncBody", Token(), false));
    Ret parsed_Scope = parse_Scope(tokens, index);
    
    if(parsed_Scope.valid){
        FuncBody.getRoot().addChild(parsed_Scope.ast);
        return Ret(true, FuncBody.getRoot(), index);
    }
    else{
        Ret error(false, Node("error", Token(), false), parsed_Scope.index);
        return error;
    }

}

Ret parse_Scope(vector<Token>& tokens, int index){
    AST Scope(Node("Scope", Token(), false));
    Ret parsed_ScopeType = parse_ScopeType(tokens, index);
    if(parsed_ScopeType.valid){
        Scope.getRoot().addChild(parsed_ScopeType.ast);
        if(tokens.at(parsed_ScopeType.index).type == "kw_open_curly"){
            Scope.getRoot().addChild(Node("kw_open_curly", tokens.at(parsed_ScopeType.index), true));
            parsed_ScopeType.index++;
            Ret parsed_ScopeBody = parse_ScopeBody(tokens, parsed_ScopeType.index);
            if(parsed_ScopeBody.valid){
                Scope.getRoot().addChild(parsed_ScopeBody.ast);
                if(tokens.at(parsed_ScopeBody.index).type == "kw_close_curly"){
                    Scope.getRoot().addChild(Node("kw_close_curly", tokens.at(parsed_ScopeBody.index), true));
                    parsed_ScopeBody.index++;

                    Ret okay(true, Scope.getRoot(), parsed_ScopeBody.index);
                }
                else{
                    Ret error(false, Node("error", Token(), false), index);
                    return error;
                }
            }
            else{
                Ret error(false, Node("error", Token(), false), index);
                return error;
            }
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_ScopeType(vector<Token>& tokens, int index){
    AST ScopeType(Node("ScopeType", Token(), false));
    if(tokens.at(index).type == "kw_Pure"){
        ScopeType.getRoot().addChild(Node("kw_Pure", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_IO"){
        ScopeType.getRoot().addChild(Node("kw_IO", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_State"){
        ScopeType.getRoot().addChild(Node("kw_State", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        return okay;
    }
    else{
        ScopeType.getRoot().addChild(Node("empty", Token(), true));
        Ret okay(true, ScopeType.getRoot(), index);
    }
}

Ret parse_ScopeBody(vector<Token>& tokens, int index){
    AST ScopeBody(Node("ScopeBody", Token(), false));
    Ret parsed_Code = parse_Code1(tokens, index);
    if(parsed_Code.valid){
        ScopeBody.getRoot().addChild(parsed_Code.ast);
        Ret okay(true, ScopeBody.getRoot(), parsed_Code.index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_Code1(vector<Token>& tokens, int index){
    AST Code(Node("Code", Token(), false));
    Ret parsed_Statement = parse_Statement(tokens, index);
    if(parsed_Statement.valid){
        Code.getRoot().addChild(parsed_Statement.ast);
        Ret parsed_Code = parse_Code2(tokens, parsed_Statement.index);
        if(parsed_Code.valid){
            Code.getRoot().addChild(parsed_Code.ast);
            Ret okay(true, Code.getRoot(), parsed_Code.index);
            return okay;
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_Code2(vector<Token>& tokens, int index){
    AST Code(Node("Code'", Token(), false));
    Ret parsed_Code = parse_Code1(tokens, index);
    if(parsed_Code.valid){
        Code.getRoot().addChild(parsed_Code.ast);
        Ret okay(true, Code.getRoot(), parsed_Code.index);
        return okay;
    }
    else{
        Code.getRoot().addChild(Node("empty", Token(), true));
        Ret okay(true, Code.getRoot(), parsed_Code.index);
        return okay;
    }
}

Ret parse_Statement(vector<Token>& tokens, int index){
    AST Statement(Node("Statement", Token(), false));
    Ret parsed_IO = parse_IO(tokens, index);
    Ret parsed_Return = parse_Return(tokens, index);
    if(parsed_IO.valid){
        Statement.getRoot().addChild(parsed_IO.ast);
        Ret okay(true, Statement.getRoot(), parsed_IO.index);
        return okay;
    }
    else if(parsed_Return.valid){
        Statement.getRoot().addChild(parsed_Return.ast);
        Ret okay(true, Statement.getRoot(), parsed_Return.index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_IO(vector<Token>& tokens, int index){
    AST IO(Node("IO", Token(), false));
    Ret parsed_Output = parse_Output(tokens, index);
    if(parsed_Output.valid){
        IO.getRoot().addChild(parsed_Output.ast);
        Ret okay(true, IO.getRoot(), parsed_Output.index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_Return(vector<Token>& tokens, int index){
    AST Return(Node("Return", Token(), false));
    if(tokens.at(index).type == "kw_return"){
        Return.getRoot().addChild(Node("kw_return", tokens.at(index), true));
        index++;
        //TODO expand return for more values not just 0
        if(tokens.at(index).type == "int"){
            Return.getRoot().addChild(Node("int", tokens.at(index), true));
            index++;
            if(tokens.at(index).type == "kw_semicolon"){
                Return.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
                index++;
                Ret okay(true, Return.getRoot(), index);
            }
            else{
                Ret error(false, Node("error", Token(), false), index);
                return error;
            }
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}

Ret parse_Output(vector<Token>& tokens, int index){
    AST Output(Node("Output", Token(), false));
    if(tokens.at(index).type == "kw_output"){
        Output.getRoot().addChild(Node("kw_output", tokens.at(index), true));
        index++;
        //TODO expand output for more strings/ string concats not just string
        if(tokens.at(index).type == "string"){
            Output.getRoot().addChild(Node("string", tokens.at(index), true));
            index++;
            if(tokens.at(index).type == "kw_semicolon"){
                Output.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
                index++;
                Ret okay(true, Output.getRoot(), index);
            }
            else{
                Ret error(false, Node("error", Token(), false), index);
                return error;
            }
        }
        else{
            Ret error(false, Node("error", Token(), false), index);
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token(), false), index);
        return error;
    }
}