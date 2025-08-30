#include <vector>
#include <string>
#include <algorithm>

#include "token.hpp"
#include "regex.hpp"
#include "tokenizer.hpp"

using namespace std;

TokenData next_token(string& s, int& index, int& line, int& col){
    int start_col = -1;
    string token = "";
    //TODO spaces in strings and char
    //TODO replace with regex
    //TODO check for things like (x + y) where there is no space between tokens for more then one space symbols
    while(index < static_cast<int>(s.size()) && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        if(s[index] == '\n'){
            line++;
            col = 1;
        }
        else{
            col++;
        }
        index++;
    }

    while(index < static_cast<int>(s.size()) && !(s[index] == ' ' || s[index] == '\n' || s[index] == '\t')){
        
        if(find(symbols.begin(), symbols.end(), string(1, s[index])) != symbols.end()){
            if(start_col == -1){
                token += s[index];
                start_col = col;
                index++;
                col++;

                //check for 2 or 3 lenght symbols also
                while(index < static_cast<int>(s.size())){
                    string temp = token;
                    temp += s[index];
                    //cout << "token: " << token << "\n";
                    //cout << "temp: " << temp << "\n";
                    //cout << "index: " << s[index] << "\n";
                    //cout << "index  + 1: " << s[index + 1] << "\n";
                    if(find(symbols.begin(), symbols.end(), temp) != symbols.end()){
                        token += s[index];
                        index++;
                        col++;
                        //cout << "found " << token << "\n";
                    }
                    else{
                        //cout << "final token: " << token << "\n";
                        break;
                    }
                }

                return {token, line, start_col};
            }
            else{
                return {token, line, start_col};
            }
        }
        
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