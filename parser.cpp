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
        Node error("error", "error", false);
        return AST(error);
    }
}

Ret parse_Program(vector<Token>& tokens, int index){
    Ret parsed_Main = parse_Main(tokens, index);
    if(parsed_Main.valid){
        return parsed_Main;
    }
    else{
        Ret error(false, AST(Node("error", "error", false)), index);
        return error;
    }
}

Ret parse_Main(vector<Token>& tokens, int index);
Ret parse_MainDef(vector<Token>& tokens, int index);
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