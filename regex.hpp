#ifndef REGEX_HPP
#define REGEX_HPP

#include <regex>

#include "token.hpp"
#include "tokenizer.hpp"

using namespace std;

//types
//TODO increacse char and string charter support
inline const regex re_int(R"(^-?\d+$)");
inline const regex re_float(R"(^-?\d+\.\d+$)");
inline const regex re_char(R"(^'[a-zA-Z0-9_ ]'$)");
inline const regex re_bool(R"(\b(true|false)\b)");
inline const regex re_string(R"(^\"[a-zA-Z0-9_ ]+\"$)");

//keywords
//types
inline const regex re_kw_int(R"(^int$)");
inline const regex re_kw_float(R"(^float$)");
inline const regex re_kw_char(R"(^char$)");
inline const regex re_kw_bool(R"(^bool$)");
inline const regex re_kw_string(R"(^string$)");

inline const regex re_kw_main(R"(^main$)");
inline const regex re_kw_arrow(R"(^->$)");

//peren, braces, and brackes oh my!
inline const regex re_kw_open_curly(R"(^\{$)");
inline const regex re_kw_close_curly(R"(^\}$)");

inline const regex re_kw_semicolon(R"(^;$)");

//Scope
inline const regex re_kw_IO(R"(^IO$)");
inline const regex re_kw_State(R"(^State$)");
inline const regex re_kw_Pure(R"(^Pure$)");

//functions
inline const regex re_kw_output(R"(^output$)");
inline const regex re_kw_return(R"(^return$)");


string string_to_token(string& s){
    //keywords
    //types
    if(regex_match(s, re_kw_int)){
        return "kw_int";
    }
    else if(regex_match(s, re_kw_float)){
        return "kw_float";
    }
    else if(regex_match(s, re_kw_bool)){
        return "kw_bool";
    }
    else if(regex_match(s, re_kw_char)){
        return "kw_char";
    }
    else if(regex_match(s, re_kw_string)){
        return "kw_string";
    }
    
    else if(regex_match(s, re_kw_main)){
        return "kw_main";
    }
    else if(regex_match(s, re_kw_arrow)){
        return "kw_arrow";
    }
    
    //symbols
    else if(regex_match(s, re_kw_open_curly)){
        return "kw_open_curly";
    }
    else if(regex_match(s, re_kw_close_curly)){
        return "kw_close_curly";
    }
    else if(regex_match(s, re_kw_semicolon)){
        return "kw_semicolon";
    }
    
    //Scope
    else if(regex_match(s, re_kw_IO)){
        return "kw_IO";
    }
    else if(regex_match(s, re_kw_State)){
        return "kw_State";
    }
    else if(regex_match(s, re_kw_Pure)){
        return "kw_Pure";
    }

    //functions
    else if(regex_match(s, re_kw_output)){
        return "kw_output";
    }
    else if(regex_match(s, re_kw_return)){
        return "kw_return";
    }


    //user input
    //types
    else if(regex_match(s, re_int)){
        return "int";
    }
    else if(regex_match(s, re_float)){
        return "float";
    }
    else if(regex_match(s, re_char)){
        return "char";
    }
    else if(regex_match(s, re_bool)){
        return "bool";
    }
    else if(regex_match(s, re_string)){
        return "string";
    }
    else{
        return "error";
    }
}

#endif
