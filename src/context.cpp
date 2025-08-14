#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>

#include "context.hpp"

using namespace std;

Table::Table(){
    scope_depth = 0;
    vector<Var> scope;
    table.push_back(scope);
}

void Table::push_scope(){
    vector<Var> scope;
    table.push_back(scope);
    scope_depth++;
}

void Table::pop_scope(){
    table.pop_back();
    archive.push_back(table.back());
    scope_depth--;
}

void Table::add_var(Var var){
    table.at(scope_depth).push_back(var);
}

void Table::mod_value(string var_name, string var_value){
    bool found = false;
    for(int i = scope_depth; scope_depth >= 0; i--){
            for(int j = 0; j < table.at(i).size(); j++){
                if(table.at(i).at(j).name == var_name && !found){
                    if(!table.at(i).at(j).mut){
                        cerr << "error at line: " << table.at(i).at(j).line << " column: " << table.at(i).at(j).col << " modifying non-mutable variable\n";
                        exit(1);
                    }
                    table.at(i).at(j).value = var_value;
                    found = true;
                }
            }
    }

}

string Table::get_value(string var_name){
    for(int i = scope_depth; scope_depth >= 0; i--){
        for(int j = 0; j < table.at(i).size(); j++){
            if(table.at(i).at(j).name == var_name){
                return table.at(i).at(j).value;
            }
        }
    }
    cerr << "error tryed to accuss indentifer without assocated value\n";
    exit(1);
}

void Table::print_table(){
    cout << "table\n";
    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table.at(i).size(); j++){
            table.at(i).at(j).print_var();
        }
    }
    cout << "archive\n";
    for(int i = 0; i < archive.size(); i++){
        for(int j = 0; j < archive.at(i).size(); j++){
            archive.at(i).at(j).print_var();
        }
    }
}