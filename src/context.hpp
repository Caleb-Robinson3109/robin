#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <string>
#include <vector>

using namespace std;

class Var{
public:
    string name;
    bool mut;
    string value;
    string type;
    int line;
    int col;

    void print_var(){
        cout << line << (mut ? " mut " : " ") << type << " " << name << " = " << value << "\n";
    }
};

class Table{
private:
    vector<vector<Var>> table;
    vector<vector<Var>> archive;
    int scope_depth;

public:
    void push_scope();
    void pop_scope();
    void add_var(Var var);
    void mod_value(string var_name, string var_value);
    string get_value(string var_name);
    void print_table();

    Table();
};

#endif