#include <fstream>

#include "ast.hpp"

void generator(AST& tree);

string node_to_cpp(Node& node);

void gen_Program(Node& node, ofstream& file);
void gen_Main(Node& node, ofstream& file);
void gen_MainDef(Node& node, ofstream& file);
void gen_FuncBody(Node& node, ofstream& file);
void gen_Scope(Node& node, ofstream& file);
void gen_ScopeBody(Node& node, ofstream& file);
void gen_Code(Node& node, ofstream& file);
void gen_Codep(Node& node, ofstream& file);
void gen_Statement(Node& node, ofstream& file);
void gen_IO(Node& node, ofstream& file);
void gen_Return(Node& node, ofstream& file);
void gen_Output(Node& node, ofstream& file);
void gen_Decloration(Node& node, ofstream& file);
void gen_Mut(Node& node, ofstream& file);
void gen_Let(Node& node, ofstream& file);
void gen_Type(Node& node, ofstream& file);
void gen_Value(Node& node, ofstream& file);
void gen_String(Node& node, ofstream& file);
void gen_Int(Node& node, ofstream& file);
void gen_Char(Node& node, ofstream& file);
void gen_Bool(Node& node, ofstream& file);
void gen_Float(Node& node, ofstream& file);
void gen_Expression(Node& node, ofstream& file);
void gen_Expressionp(Node& node, ofstream& file);
void gen_Term(Node& node, ofstream& file);
void gen_Factor(Node& node, ofstream& file);
void gen_Operator(Node& node, ofstream& file);
void gen_Number(Node& node, ofstream& file);