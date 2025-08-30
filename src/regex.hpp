#ifndef REGEX_HPP
#define REGEX_HPP

#include <regex>
#include <vector>

#include "token.hpp"
#include "tokenizer.hpp"

using namespace std;

//types
//TODO increacse char and string charter support
inline const regex re_int(R"(^-?\d+$)");
inline const regex re_float(R"(^-?\d+\.\d+$)");
inline const regex re_char(R"(^'[a-zA-Z0-9_]'$)");
inline const regex re_bool(R"(\b(true|false)\b)");
inline const regex re_string(R"(^\"([a-zA-Z0-9_]|\\[nt\"\\])*\"$)");
inline const regex re_ident(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");

//keywords
//types
inline const regex re_kw_int(R"(^int$)");
inline const regex re_kw_float(R"(^float$)");
inline const regex re_kw_char(R"(^char$)");
inline const regex re_kw_bool(R"(^bool$)");
inline const regex re_kw_string(R"(^string$)");

inline const regex re_kw_main(R"(^main$)");
inline const regex re_kw_mut(R"(^mut$)");

//peren, braces, and brackes oh my! (symbols)
inline const regex re_kw_arrow(R"(^->$)");
inline const regex re_kw_open_curly(R"(^\{$)");
inline const regex re_kw_close_curly(R"(^\}$)");
inline const regex re_kw_equal(R"(^=$)");
inline const regex re_kw_semicolon(R"(^;$)");

inline const regex re_kw_plus(R"(^+$)");
inline const regex re_kw_minus(R"(^-$)");
inline const regex re_kw_multiply(R"(^*$)");
inline const regex re_kw_divide(R"(^/$)");
inline const regex re_kw_mod(R"(^%$)");
inline const regex re_kw_open_peren(R"(^($)");
inline const regex re_kw_close_peren(R"(^)$)");

//Scope
inline const regex re_kw_IO(R"(^IO$)");
inline const regex re_kw_State(R"(^State$)");
inline const regex re_kw_Pure(R"(^Pure$)");

//functions
inline const regex re_kw_output(R"(^output$)");
inline const regex re_kw_return(R"(^return$)");

//vectors of types of tokens
vector<regex> symbols;
symbols.push_back(re_kw_arrow);
symbols.push_back(re_kw_open_curly);
symbols.push_back(re_kw_close_curly);
symbols.push_back(re_kw_equal);
symbols.push_back(re_kw_semicolon);
symbols.push_back(re_kw_plus);
symbols.push_back(re_kw_minus);
symbols.push_back(re_kw_multiply);
symbols.push_back(re_kw_divide);
symbols.push_back(re_kw_mod);
symbols.push_back(re_kw_open_peren);
symbols.push_back(re_kw_close_peren);

string string_to_token(string& s);

#endif
