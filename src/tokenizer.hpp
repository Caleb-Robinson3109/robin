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

TokenData next_token(string& s, int& index, int& line, int& col);

vector<Token> tokenizer (string& s);

#endif
