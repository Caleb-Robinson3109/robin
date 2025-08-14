#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "token.hpp"
#include "ast.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "generator.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Needs correct number of arguments\nUsing default hello.rob file\n";
        //return 1;
    }
    fstream robin("hello.rob");
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

    robin.close();

    vector<Token> tokens = tokenizer(contents);

    //for(Token t : tokens){
    //    t.print_token_struct();
    //}

    AST parsed = parser(tokens);

    //parsed.printAST();

    
    if(parsed.has_error()){
        cerr << "there was an error while parsing the code\n";
        return 1;
    }

    generator(parsed);
    
    return 0;
}
