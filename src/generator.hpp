#include <fstream>

#include "ast.hpp"

void generator(AST& tree);

void generator_helper(Node& node, ofstream& file);

string node_to_cpp(Node& node);