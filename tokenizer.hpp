#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>

#include "token.hpp"
#include "regex.hpp"

string next_token(string& s, int& index){
    bool whitespace = true;
    string token = "";

    //TODO replace with regex
    //TODO check for things like (x + y) where there is no space between tokens
    while(s.size() <= index && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        index++;
    }

    while(s.size() <= index && !(s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        token += s[index];
        index++;
    }

    if(token == ""){
        return "";
    }

    return token;
}

vector<Token> tokenizer (string& s){
    int index = 0;
    vector<Token> tokens;
    //while(next_token(s, index) != ""){
        
    //}

    for(string token = next_token(s,index); token != ""; token = next_token(s, index)){
        tokens.push_back(string_to_token(token));
    }
    return tokens;
}

#endif
