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

void AST::printASTHelper(Node& n, int depth){
    /*
    for(int i = 0; i < depth; i++){
        cout << " ";
    }

    cout << left << setw(20) << n.getType() << right << setw(4) << depth << "\n";

    for (Node child : n.getChildren()){
        printASTHelper(child, depth + 1);
    }
    */

    cout << right << setw(7) << depth;
    cout << string(depth, ' ');
    cout << n.getType() << " - " << n.getValue().value << "\n";

    // Recurse into children
    for (Node child : n.getChildren()) {
        printASTHelper(child, depth + 1);
    }
}

void AST::printAST() {
    int depth = 0;

    cout << left << setw(20) << root.getType() << right << setw(4) << depth << "\n";

    for(Node child : root.getChildren()){
        printASTHelper(child, 1);
    }
}

vector<Node> Node::compressor() {
    vector<Node> compressed_list;

    compressed_list.push_back(Node(this->type, this->value, this->terminal));

    auto helper = [&compressed_list](auto&& self, const Node& node) -> void {
        for (const Node& child : node.getChildren()) {
            compressed_list.push_back(Node(child.type, child.value, child.terminal));
            self(self, child);
        }
    };

    helper(helper, *this);
    return compressed_list;
}