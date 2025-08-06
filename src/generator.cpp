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

    generator_helper(tree.getRoot(), cpp);

    cpp.close();
}