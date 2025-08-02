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
    Ret parsed_MainDef = parse_MainDef(tokens, index);
    AST Main(Node("Main", Token(), false));
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

Ret parse_FuncBody(vector<Token>& tokens, int index);
Ret parse_Scope(vector<Token>& tokens, int index);
Ret parse_ScopeType(vector<Token>& tokens, int index);
Ret parse_ScopeBody(vector<Token>& tokens, int index);
Ret parse_Code1(vector<Token>& tokens, int index);
Ret parse_Code2(vector<Token>& tokens, int index);
Ret parse_Statement(vector<Token>& tokens, int index);
Ret parse_IO(vector<Token>& tokens, int index);
Ret parse_Return(vector<Token>& tokens, int index);
Ret parse_Output(vector<Token>& tokens, int index);