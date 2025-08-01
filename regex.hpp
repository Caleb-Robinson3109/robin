#ifndef REGEX_HPP
#define REGEX_HPP

#include <regex>

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
inline const regex re_type_int(R"(^int$)");
inline const regex re_type_float(R"(^float$)");
inline const regex re_type_char(R"(^char$)");
inline const regex re_type_bool(R"(^bool$)");
inline const regex re_type_string(R"(^string$)");

inline const regex re_main(R"(^main$)");
inline const regex re_type_arrow(R"(^->$)");

//peren, braces, and brackes oh my!
inline const regex re_open_curly(R"(^{$)");
inline const regex re_close_curly(R"(^}$)");

//Scope
inline const regex re_IO(R"(^IO$)");
inline const regex re_State(R"(^State$)");
inline const regex re_Pure(R"(^Pure$)");



#endif
