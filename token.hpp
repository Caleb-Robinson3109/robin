#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

using namespace std;

struct Token{
    string type;
    string value;
    
    void print_token_struct() const {
        cout << "Token.type = " << type << " Token.value = " << value << "\n";
    }
};

#endif
