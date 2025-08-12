#include <string>
#include <vector>

using namespace std;

class Var{
public:
    string name;
    bool mut;
    string value;
    string type;
};

class Table{
private:
    vector<vector<Var>> table;
    int scope_depth = 0;

public:
    void push_scope();
    void pop_scope();
    void add_var(Var var);
    void mod_value(string var_name, string var_value);
    string get_value(string var_name);

};