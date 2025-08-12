#include <string>
#include <vector>

#include "context.hpp"

using namespace std;

void Table::push_scope();
void Table::pop_scope();
void Table::add_var(Var var);
void Table::mod_value(string var_name, string var_value);
string Table::get_value(string var_name);