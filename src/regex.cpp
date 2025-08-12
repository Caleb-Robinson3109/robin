#include <string>
#include <regex>

#include "regex.hpp"

using namespace std;

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
    else if(regex_match(s, re_ident)){
        return "ident";
    }
    else{
        return "error";
    }
}