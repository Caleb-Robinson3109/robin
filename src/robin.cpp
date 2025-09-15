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

    //parse the args
    string cpp_filename = "gen/";
    string rob_filename = "rob/";

    //argv[1] input filename
    if(argc > 1){
        rob_filename += argv[1];
    }
    else{
        cerr << "Needs correct number of arguments\nUsing default hello.rob file\n";
        rob_filename += "hello.rob";
        //return 1;
    }
    fstream robin(rob_filename);

    //argv[2] output filename
    if(argc > 2){
        cpp_filename += argv[2];
    }
    else{
        cpp_filename += "gen.cpp";
    }

    if(!robin){
        cerr << "Cannot open file " << rob_filename << "\n";
        return 1;
    }

    stringstream buffer;
    buffer << robin.rdbuf();

    string contents = buffer.str();

    robin.close();

    //cout << "tokenizing the code\n";

    vector<Token> tokens = tokenizer(contents);

    //cout << "Done tokenizing\n";

    //for(Token t : tokens){
    //    t.print_token_struct();
    //}

    AST parsed = parser(tokens);

    //parsed.printAST();

    
    if(parsed.has_error()){
        cerr << "there was an error while parsing the code\n";
        return 1;
    }

    generator(parsed, cpp_filename);
    
    return 0;
}
