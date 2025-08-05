#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>

#include "token.hpp"
#include "regex.hpp"

using namespace std;

struct TokenData{
    string token;
    unsigned long long line;
    unsigned long long col; 
};

TokenData next_token(string& s, int& index){
    static int line = 1;
    static int col = 1;
    string token = "";
    //TODO spaces in strings and char
    //TODO replace with regex
    //TODO check for things like (x + y) where there is no space between tokens
    while(index < s.size() && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        index++;
        if(s[index] == '\n'){
            line++;
            col = 1;
        }
        else{
            col++;
        }
    }

    while(index < s.size() && !(s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        token += s[index];
        index++;
        col++;
    }

    return {token, line, col};
}

vector<Token> tokenizer (string& s){
    int index = 0;
    vector<Token> tokens;

    for(TokenData token_data = next_token(s,index); token_data.token != ""; token_data = next_token(s, index)){
        tokens.push_back(Token(string_to_token(token_data.token), token_data.token, token_data.line, token_data.col));
    }
    return tokens;
}

#endif
