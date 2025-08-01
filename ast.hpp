#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node {
private:
    string type;
    string value;
    bool terminal;
    vector<Node> children;

public:
    // Constructor
    Node(const string& t, const string& v, bool x)
        : type(t), value(v), terminal(x) {}

    // Getters
    string getType() const { return type; }
    string getValue() const { return value; }
    bool getTerminal() const { return terminal; }
    vector<Node>& getChildren() { return children; }

    // Setters
    void setType(const string& t) { type = t; }
    void setValue(const string& v) { value = v; }
    void setTerminal(bool x) { terminal = x; }

    // Add child
    void addChild(const Node& node) {
        children.push_back(node);
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
};
