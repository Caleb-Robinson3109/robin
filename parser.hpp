#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>

#include "token.hpp"
#include "ast.hpp"

using namespace std;

struct Ret{
    bool valid;
    AST ast;
};

AST parser (vector<Token>& tokens, int index);
Ret parse_Program(vector<Token>& tokens, int index);
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

#endif