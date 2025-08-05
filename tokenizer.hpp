#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>

#include "token.hpp"
#include "regex.hpp"

using namespace std;

struct TokenData{
    string token;
    int line;
    int col; 
};

TokenData next_token(string& s, int& index, int& line, int& col){
    int start_col = -1;
    string token = "";
    //TODO spaces in strings and char
    //TODO replace with regex
    //TODO check for things like (x + y) where there is no space between tokens
    while(index < s.size() && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        if(s[index] == '\n'){
            //cout << "\n\nLINEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE " << line << "\n\n";
            line++;
            col = 1;
        }
        else{
            col++;
        }
        index++;
    }

    while(index < s.size() && !(s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        token += s[index];
        if(start_col == -1){
            start_col = col;
        }
        index++;
        col++;
    }
    //cout << "line: " << line << " col: " << col << endl;
    return {token, line, start_col};
}

vector<Token> tokenizer (string& s){
    int index = 0;
    int line = 1;
    int col = 1;
    vector<Token> tokens;

    for(TokenData token_data = next_token(s,index, line, col); token_data.token != ""; token_data = next_token(s, index, line, col)){
        
        tokens.push_back(Token(string_to_token(token_data.token), token_data.token, token_data.line, token_data.col));
    }
    return tokens;
}

#endif
