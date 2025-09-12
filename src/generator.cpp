#include <fstream>
#include <cstdlib>
#include <iostream>

#include "generator.hpp"
#include "ast.hpp"
#include "token.hpp"

using namespace std;

string node_to_cpp(Node& node){
    return node.getValue().value + (string)" ";
}

string node_to_cpp2(Node& node){
    if(node.getValue().type == "int"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "float"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "bool"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "char"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "string"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_int"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_float"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_bool"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_char"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_string"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_main"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_arrow"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_open_curly"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_close_curly"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_semicolon"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_IO"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_State"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_Pure"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_output"){
        return node.getValue().value + (string)" ";
    }
    else if(node.getValue().type == "kw_return"){
        return node.getValue().value + (string)" ";
    }
    else{
        return "";
    }
}

void generator(AST& tree){
    ofstream cpp("./gen/gen.cpp");

    if(!cpp){
        cerr << "error creating .cpp file\n";
        exit(1);
    }

    gen_Program(tree.getRoot(), cpp);

    cpp.close();
}

void gen_Program(Node& node, ofstream& file){
    //cout << "program\n";
    vector<Node> children = node.getChildren();
    file << "#include <iostream>\n";
    file << "#include <string>\n";
    gen_Main(children.at(0), file);
}

void gen_Main(Node& node, ofstream& file){
    //cout << "main\n";
    vector<Node> children = node.getChildren();
    gen_MainDef(children.at(0), file);
    gen_FuncBody(children.at(1), file);
}

void gen_MainDef(Node& node, ofstream& file){
    //cout << "maindef\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(2));
    file << node_to_cpp(children.at(0));
    file << "()\n";
}

void gen_FuncBody(Node& node, ofstream& file){
    //cout << "funcbody\n";
    vector<Node> children = node.getChildren();
    gen_Scope(children.at(0), file);
}

void gen_Scope(Node& node, ofstream& file){
    //cout << "scope\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(1));
    file << "\n";
    gen_ScopeBody(children.at(2), file);
    file << node_to_cpp(children.at(3));
    file << "\n";
}

void gen_ScopeBody(Node& node, ofstream& file){
    //cout << "scopebody\n";
    vector<Node> children = node.getChildren();
    gen_Code(children.at(0), file);
}

void gen_Code(Node& node, ofstream& file){
    //cout << "code\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Statement"){
        gen_Statement(children.at(0), file);
    }
    else if(children.at(0).getType() == "Scope"){
        gen_Scope(children.at(0), file);
    }
    gen_Codep(children.at(1), file);
}

void gen_Codep(Node& node, ofstream& file){
    //cout << "code'\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "empty"){
        return;
    }
    else if(children.at(0).getType() == "Code"){
        gen_Code(children.at(0), file);
    }
}

void gen_Statement(Node& node, ofstream& file){
    //cout << "stmt\n";
    vector<Node> children = node.getChildren();
    //cout << "\t" << children.at(0).getValue().type << "\n";
    if(children.at(0).getType() == "IO"){
        gen_IO(children.at(0), file);
    }
    else if(children.at(0).getType() == "Return"){
        gen_Return(children.at(0), file);
    }
    else if(children.at(0).getType() == "Decloration"){
        gen_Decloration(children.at(0), file);
    }
}

void gen_IO(Node& node, ofstream& file){
    //cout << "io\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Output"){
        gen_Output(children.at(0), file);
    }
}

void gen_Return(Node& node, ofstream& file){
    //cout << "ret\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
    file << node_to_cpp(children.at(1));
    file << node_to_cpp(children.at(2));
    file << "\n";
}

void gen_Output(Node& node, ofstream& file){
    //cout << "out\n";
    vector<Node> children = node.getChildren();
    file << "std::cout << ";
    gen_Value(children.at(1), file);
    file << node_to_cpp(children.at(2));
    file << "\n";
}

void gen_Decloration(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Mut"){
        gen_Mut(children.at(0), file);
    }
    else if(children.at(0).getType() == "Let"){
        gen_Let(children.at(0), file);
    }
}

void gen_Mut(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Type(children.at(1), file);
    file << node_to_cpp(children.at(2));
    file << node_to_cpp(children.at(3));
    file << node_to_cpp(children.at(4));
    file << node_to_cpp(children.at(5));
    file << "\n";
}

void gen_Let(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << "const ";
    gen_Type(children.at(0), file);
    file << node_to_cpp(children.at(1));
    file << node_to_cpp(children.at(2));
    gen_Value(children.at(3), file);
    file << node_to_cpp(children.at(4));
    file << "\n";
}

void gen_Type(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "kw_string"){
        file << "std::";
    }
    file << node_to_cpp(children.at(0));
}

void gen_Value(Node& node, ofstream& file){
     vector<Node> children = node.getChildren();
     if(children.at(0).getType() == "String"){
        gen_String(children.at(0), file);
     }
     else if(children.at(0).getType() == "Expression"){
        gen_Expression(children.at(0), file);
     }
     else if(children.at(0).getType() == "Char"){
        gen_Char(children.at(0), file);
     }
     else if(children.at(0).getType() == "Bool"){
        gen_Bool(children.at(0), file);
     }
}

void gen_String(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Int(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    //cout << "gen int\n";
    //children.at(0).printNode();
    file << node_to_cpp(children.at(0));
}

void gen_Char(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Bool(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Float(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Expression(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Term(children.at(0), file);
    gen_Expressionp(children.at(1), file);
}

void gen_Expressionp(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "empty"){
        return;
    }
    gen_Operator(children.at(0), file);
    gen_Term(children.at(1), file);
    gen_Expressionp(children.at(2), file);
}

void gen_Term(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Factor"){
        gen_Factor(children.at(0), file);
    }
    else{
        file << node_to_cpp(children.at(0));
        gen_Expression(children.at(1), file);
        file << node_to_cpp(children.at(2));
    }
}

void gen_Factor(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Number(children.at(0), file);
}

void gen_Operator(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Number(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Int"){
        gen_Int(children.at(0), file);
    }
    else{
        gen_Float(children.at(0), file);
    }
}