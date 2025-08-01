#ifndef REGEX_HPP
#define REGEX_HPP

#include <regex>

#include "token.hpp"

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


Token string_to_token(string& s){
    //keywords
    //types
    if(regex_match(s, re_kw_int)){
        return {"kw_int", s};
    }
    else if(regex_match(s, re_kw_float)){
        return {"kw_float", s};
    }
    else if(regex_match(s, re_kw_bool)){
        return {"kw_bool", s};
    }
    else if(regex_match(s, re_kw_char)){
        return {"kw_char", s};
    }
    else if(regex_match(s, re_kw_string)){
        return {"kw_string", s};
    }
    
    else if(regex_match(s, re_kw_main)){
        return {"kw_main", s};
    }
    else if(regex_match(s, re_kw_arrow)){
        return {"kw_arrow", s};
    }
    
    //symbols
    else if(regex_match(s, re_kw_open_curly)){
        return {"kw_open_curly", s};
    }
    else if(regex_match(s, re_kw_close_curly)){
        return {"kw_close_curly", s};
    }
    else if(regex_match(s, re_kw_semicolon)){
        return {"kw_semicolon", s};
    }
    
    //Scope
    else if(regex_match(s, re_kw_IO)){
        return {"kw_IO", s};
    }
    else if(regex_match(s, re_kw_State)){
        return {"kw_State", s};
    }
    else if(regex_match(s, re_kw_Pure)){
        return {"kw_Pure", s};
    }

    //functions
    else if(regex_match(s, re_kw_output)){
        return {"kw_output", s};
    }
    else if(regex_match(s, re_kw_return)){
        return {"kw_return", s};
    }


    //user input
    //types
    else if(regex_match(s, re_int)){
        return {"int", s};
    }
    else if(regex_match(s, re_float)){
        return {"float", s};
    }
    else if(regex_match(s, re_char)){
        return {"char", s};
    }
    else if(regex_match(s, re_bool)){
        return {"bool", s};
    }
    else if(regex_match(s, re_string)){
        return {"string", s};
    }
    else{
        return {"error", s};
    }
}

#endif
