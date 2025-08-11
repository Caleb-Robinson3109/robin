#include <fstream>
#include <cstdlib>
#include <iostream>

#include "generator.hpp"
#include "ast.hpp"
#include "token.hpp"

using namespace std;

string node_to_cpp(Node& node){
    if(node.getValue().type == "kw_int"){
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
    else if(node.getValue().type == "kw_float"){
        return node.getValue().value + (string)" ";
    }
}

void generator_helper(Node& node, ofstream& file){
    file << node_to_cpp(node);

    for(Node child : node.getChildren()){
        generator_helper(child, file);
    }
}

void generator(AST& tree){
    ofstream cpp("./gen/out.cpp");

    if(!cpp){
        cerr << "error creating .cpp file\n";
        exit(1);
    }

    gen_Program(tree.getRoot(), cpp);

    cpp.close();
}

void gen_Program(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Main(children.at(0), file);
}

void gen_Main(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_MainDef(children.at(0), file);
    gen_FuncBody(children.at(1), file);
}

void gen_MainDef(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(2));
    file << node_to_cpp(children.at(0));
    file << "()\n";
}

void gen_FuncBody(Node& node, ofstream& file);
void gen_Scope(Node& node, ofstream& file);
void gen_ScopeType(Node& node, ofstream& file);
void gen_ScopeBody(Node& node, ofstream& file);
void gen_Code(Node& node, ofstream& file);
void gen_Codep(Node& node, ofstream& file);
void gen_Statement(Node& node, ofstream& file);
void gen_IO(Node& node, ofstream& file);
void gen_voidurn(Node& node, ofstream& file);
void gen_Output(Node& node, ofstream& file);