#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "token.hpp"
#include "ast.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Needs correct number of arguments\nUsing default hello.txt file\n";
        //return 1;
    }
    fstream robin("hello.txt");
    if(argc == 2){
            robin.close();
            robin.open(argv[1], ios::in);
    }

    if(!robin){
        cerr << "Cannot open file";
        return 1;
    }

    stringstream buffer;
    buffer << robin.rdbuf();

    string contents = buffer.str();    

    vector<Token> tokens = tokenizer(contents);

    /*for(Token t : tokens){
        t.print_token_struct();
    }*/

    AST parsed = parser(tokens);
    
    robin.close();
    return 0;
}
