#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>

#include "token.hpp"
#include "ast.hpp"
#include "context.hpp"

using namespace std;

class Ret {
public:
    bool valid;
    Node ast;
    int index;

    Ret(bool v, const Node& a, int i)
        : valid(v), ast(a), index(i) {}

    void printRet(){
        cout << "valid: " << valid << " index: " << index << " ast: ";
        ast.printNode();
    }
};

bool type_check(Var& var, Token& token);

AST parser (vector<Token>& tokens);
Ret parse_Program(vector<Token>& tokens, int index);
Ret parse_Main(vector<Token>& tokens, int index);
Ret parse_MainDef(vector<Token>& tokens, int index);
Ret parse_FuncBody(vector<Token>& tokens, int index);
Ret parse_Scope(vector<Token>& tokens, int index);
Ret parse_ScopeType(vector<Token>& tokens, int index);
Ret parse_ScopeBody(vector<Token>& tokens, int index);
Ret parse_Code(vector<Token>& tokens, int index);
Ret parse_Codep(vector<Token>& tokens, int index);
Ret parse_Statement(vector<Token>& tokens, int index);
Ret parse_IO(vector<Token>& tokens, int index);
Ret parse_Return(vector<Token>& tokens, int index);
Ret parse_Output(vector<Token>& tokens, int index);
Ret parse_Decloration(vector<Token>& tokens, int index);
Ret parse_Mut(vector<Token>& tokens, int index);
Ret parse_Let(vector<Token>& tokens, int index);
Ret parse_Type(vector<Token>& tokens, int index);
Ret parse_Value(vector<Token>& tokens, int index);
Ret parse_String(vector<Token>& tokens, int index);
Ret parse_Int(vector<Token>& tokens, int index);
Ret parse_Char(vector<Token>& tokens, int index);
Ret parse_Bool(vector<Token>& tokens, int index);
Ret parse_Float(vector<Token>& tokens, int index);


#endif