#include <vector>
#include <string>

#include "token.hpp"

string next_token(string& s, int& index){
    bool whitespace = true;
    string token = "";

    //TODO replace with regex
    //TODO check for things like (x + y) where there is no space between tokens
    while(s.size() <= index && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        index++;
    }

    while(s.size <= index && !(s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
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

    while(next_token(s, index) != ""){
        //do stuff
    }
}





