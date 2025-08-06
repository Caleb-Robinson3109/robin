#include <iostream>

#include "ast.hpp"

using namespace std;

void Node::printNode() {
    cout << "Node - type: " << type << " terminal: " << terminal << " value: ";
    value.print_token_struct();

    cout << "children:\n";
    for (Node child : children){
        child.getValue().print_token_struct();
    }
    cout << "---------------------------------------------------------\n";
}