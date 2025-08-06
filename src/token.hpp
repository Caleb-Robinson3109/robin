#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

using namespace std;

class Token{
public:
    string type;
    string value;
    int line;
    int col;
    
    Token(string t, string v, int l, int c){
        type = t;
        value = v;
        line = l;
        col = c;
    }

    void print_token_struct() const {
        cout << "Token.type = " << type << ", Token.value = " << value << ", Token.line = " << line <<  ", Token.col = " << col << "\n";
    }
};

#endif
