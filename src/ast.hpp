#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

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

    void printNode();
};

class AST {
private:
    Node root;

public:
    AST(const Node& node) : root(node) {}

    Node& getRoot() {
        return root;
    }

    void printASTHelper(Node& n, int depth);

    void printAST();

    bool has_error_helper(Node& node){
        for(Node child : node.getChildren()){
            if(child.getValue().type == "error"){
                return true;
            }
            if(has_error_helper(child)){
                return true;
            }
        }
        return false;
    }

    bool has_error(){
        return has_error_helper(root);
    }
};

#endif
