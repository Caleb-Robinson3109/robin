#include <vector>

#include "token.hpp"
#include "ast.hpp"
#include "parser.hpp"

using namespace std;

AST parser (vector<Token>& tokens){
    //cout << "parser\n";
    int index = 0;
    Ret parsed = parse_Program(tokens, index);
    //parsed.printRet();

    if(parsed.valid){
        Node okay = parsed.ast;
        return AST(okay);
    }
    else{
        Node error("error", tokens.at(index), false);
        return AST(error);
    }
}

Ret parse_Program(vector<Token>& tokens, int index){
    //cout << "program\n";
    Ret parsed_Main = parse_Main(tokens, index);
    //parsed_Main.printRet();
    if(parsed_Main.valid){
        index = parsed_Main.index;
        Ret okay(true, parsed_Main.ast, index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Main(vector<Token>& tokens, int index){
    //cout << "main\n";
    AST Main(Node("Main", {"Main", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_MainDef = parse_MainDef(tokens, index);
    //parsed_MainDef.printRet();
    
    if(parsed_MainDef.valid){
        index = parsed_MainDef.index;
        Ret parsed_FuncBody = parse_FuncBody(tokens, index);
        Main.getRoot().addChild(parsed_MainDef.ast);
        //parsed_FuncBody.printRet();

        if(parsed_FuncBody.valid){
            Main.getRoot().addChild(parsed_FuncBody.ast);
            //parsed_MainDef.ast.printNode();
            //parsed_FuncBody.ast.printNode();
            index = parsed_FuncBody.index;
            Ret okay(true, Main.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_MainDef(vector<Token>& tokens, int index){
    //cout << "def\n";
    AST MainDef(Node("MainDef", {"MainDef", "", tokens.at(index).line, tokens.at(index).col}, false));
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
                //okay.printRet();
                return okay;
            }
            else{
                Ret error(false, Node("error", tokens.at(index), false), index);
                //error.printRet();
                return error;
            }
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_FuncBody(vector<Token>& tokens, int index){
    //cout << "body\n";
    AST FuncBody(Node("FuncBody", {"FuncBody", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Scope = parse_Scope(tokens, index);
    //parsed_Scope.printRet();
    
    if(parsed_Scope.valid){
        FuncBody.getRoot().addChild(parsed_Scope.ast);
        index = parsed_Scope.index;
        Ret okay(true, FuncBody.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }

}

Ret parse_Scope(vector<Token>& tokens, int index){
    //cout << "scope\n";
    AST Scope(Node("Scope", {"Scope", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_ScopeType = parse_ScopeType(tokens, index);
    //parsed_ScopeType.printRet();
    if(parsed_ScopeType.valid){
        //cout << "typev\n";
        Scope.getRoot().addChild(parsed_ScopeType.ast);
        index = parsed_ScopeType.index;
        if(tokens.at(index).type == "kw_open_curly"){
            //cout << "{\n";
            Scope.getRoot().addChild(Node("kw_open_curly", tokens.at(index), true));
            index++;
            Ret parsed_ScopeBody = parse_ScopeBody(tokens, index);
            //parsed_ScopeBody.printRet();
            if(parsed_ScopeBody.valid){
                Scope.getRoot().addChild(parsed_ScopeBody.ast);
                index = parsed_ScopeBody.index;
                if(tokens.at(index).type == "kw_close_curly"){
                    Scope.getRoot().addChild(Node("kw_close_curly", tokens.at(index), true));
                    index++;

                    Ret okay(true, Scope.getRoot(), index);
                    //okay.printRet();
                    return okay;
                }
                else{
                    Ret error(false, Node("error", tokens.at(index), false), index);
                    //error.printRet();
                    return error;
                }
            }
            else{
                Ret error(false, Node("error", tokens.at(index), false), index);
                //error.printRet();
                return error;
            }
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_ScopeType(vector<Token>& tokens, int index){
    //cout << "type\n";
    AST ScopeType(Node("ScopeType", {"ScopeType", "", tokens.at(index).line, tokens.at(index).col}, false));
    //cout << tokens.at(index).value << "\n";
    if(tokens.at(index).type == "kw_Pure"){
        ScopeType.getRoot().addChild(Node("kw_Pure", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(tokens.at(index).type == "kw_IO"){
        ScopeType.getRoot().addChild(Node("kw_IO", tokens.at(index), true));
        //cout << "index: " << index << "\n";
        index++;
        //cout << "index: " << index << "\n";
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(tokens.at(index).type == "kw_State"){
        ScopeType.getRoot().addChild(Node("kw_State", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        //cout << "dddddd\n";
        ScopeType.getRoot().addChild(Node("empty", {"empty", "", tokens.at(index).line, tokens.at(index).col}, true));
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
}

Ret parse_ScopeBody(vector<Token>& tokens, int index){
    //cout << "sbody\n";
    AST ScopeBody(Node("ScopeBody", {"ScopeBody", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Code = parse_Code(tokens, index);
    //parsed_Code.printRet();
    if(parsed_Code.valid){
        ScopeBody.getRoot().addChild(parsed_Code.ast);
        index = parsed_Code.index;
        Ret okay(true, ScopeBody.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Code(vector<Token>& tokens, int index){
    //cout << "code\n";
    AST Code(Node("Code", {"Code", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Statement = parse_Statement(tokens, index);
    //parsed_Statement.printRet();
    Ret parsed_Scope = parse_Scope(tokens, index);
    //parsed_Scope.printRet();
    if(parsed_Statement.valid){
        Code.getRoot().addChild(parsed_Statement.ast);
        index = parsed_Statement.index;
        Ret parsed_Codep = parse_Codep(tokens, index);
        //parsed_Codep.printRet();
        if(parsed_Codep.valid){
            Code.getRoot().addChild(parsed_Codep.ast);
            index = parsed_Codep.index;
            Ret okay(true, Code.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else if(parsed_Scope.valid){
        Code.getRoot().addChild(parsed_Scope.ast);
        index = parsed_Scope.index;
        Ret parsed_Codep = parse_Codep(tokens, index);
        //parsed_Codep.printRet();
        if(parsed_Codep.valid){
            Code.getRoot().addChild(parsed_Codep.ast);
            index = parsed_Codep.index;
            Ret okay(true, Code.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Codep(vector<Token>& tokens, int index){
    //cout << "code'\n";
    AST Code(Node("Code'", {"Code'", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Code = parse_Code(tokens, index);
    //parsed_Code.printRet();
    if(parsed_Code.valid){
        Code.getRoot().addChild(parsed_Code.ast);
        index = parsed_Code.index;
        Ret okay(true, Code.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Code.getRoot().addChild(Node("empty", {"empty", "", tokens.at(index).line, tokens.at(index).col}, true));
        Ret okay(true, Code.getRoot(), index);
        //okay.printRet();
        return okay;
    }
}

Ret parse_Statement(vector<Token>& tokens, int index){
    //cout << "stmt\n";
    AST Statement(Node("Statement", {"Statement", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_IO = parse_IO(tokens, index);
    //parsed_IO.printRet();
    Ret parsed_Return = parse_Return(tokens, index);
    //parsed_Return.printRet();
    if(parsed_IO.valid){
        Statement.getRoot().addChild(parsed_IO.ast);
        index = parsed_IO.index;
        Ret okay(true, Statement.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(parsed_Return.valid){
        Statement.getRoot().addChild(parsed_Return.ast);
        index = parsed_Return.index;
        Ret okay(true, Statement.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_IO(vector<Token>& tokens, int index){
    //cout << "io\n";
    AST IO(Node("IO", {"IO", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Output = parse_Output(tokens, index);
    //parsed_Output.printRet();
    if(parsed_Output.valid){
        IO.getRoot().addChild(parsed_Output.ast);
        index = parsed_Output.index;
        Ret okay(true, IO.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Return(vector<Token>& tokens, int index){
    //cout << "ret\n";
    AST Return(Node("Return", {"Return", "", tokens.at(index).line, tokens.at(index).col}, false));
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
                //okay.printRet();
                return okay;
            }
            else{
                Ret error(false, Node("error", tokens.at(index), false), index);
                //error.printRet();
                return error;
            }
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Output(vector<Token>& tokens, int index){
    //cout << "out\n";
    //tokens.at(index).print_token_struct();
    //tokens.at(index + 1).print_token_struct();
    //tokens.at(index+ 2).print_token_struct();
    //tokens.at(index+ 3).print_token_struct();
    AST Output(Node("Output", {"Output", "", tokens.at(index).line, tokens.at(index).col}, false));
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
                //okay.printRet();
                return okay;
            }
            else{
                Ret error(false, Node("error", tokens.at(index), false), index);
                //error.printRet();
                return error;
            }
        }
        else{
            Ret error(false, Node("error", tokens.at(index), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", tokens.at(index), false), index);
        //error.printRet();
        return error;
    }
}