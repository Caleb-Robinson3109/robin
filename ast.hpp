#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream>
#include <queue>

#include "token.hpp"

using namespace std;

class Node {
private:
    string type;
    Token value;
    bool terminal;
    vector<Node> children;

public:
    // Constructor
    Node(const string& t, const Token& v, bool x)
        : type(t), value(v), terminal(x) {}

    // Getters
    string getType() const { return type; }
    Token getValue() const { return value; }
    bool getTerminal() const { return terminal; }
    const vector<Node>& getChildren() const { return children; }

    // Setters
    void setType(const string& t) { type = t; }
    void setValue(const Token& v) { value = v; }
    void setTerminal(bool x) { terminal = x; }

    // Add child
    void addChild(const Node& node) {
        children.push_back(node);
    }

    void printNode() {
        cout << "Node - type: " << type << " terminal: " << terminal << " value: ";
        value.print_token_struct();

        cout << "children:\n";
        for (Node child : children){
            child.getValue().print_token_struct();
        }
        cout << "---------------------------------------------------------\n";
    }
};

class AST {
private:
    Node root;

public:
    AST(const Node& node) : root(node) {}

    Node& getRoot() {
        return root;
    }

    void printAST() {
        queue<Node> myQueue;
        myQueue.push(root);

        while (!myQueue.empty()) {
            int levelSize = myQueue.size(); // Number of nodes at current level

            for (int i = 0; i < levelSize; ++i) {
                Node current = myQueue.front();
                myQueue.pop();

                // Print node information (you can customize this)
                cout << "[" << current.getType() << ": ";
                current.getValue().print_token_struct();
                cout << "] ";

                // Enqueue all children of the current node
                for (const Node& child : current.getChildren()) {
                    myQueue.push(child);
                }
            }

            cout << "\n"; // Newline after finishing a level
        }
    } 
};

#endif
