#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

#include "generator.hpp"
#include "ast.hpp"
#include "token.hpp"
#include "parser.hpp"

using namespace std;

string node_to_cpp(Node& node){
    return node.getValue().value + (string)" ";
}

void generator(AST& tree, string filename){
    ofstream cpp(filename);

    if(!cpp){
        cerr << "error creating " << filename << " file\n";
        exit(1);
    }

    gen_Program(tree.getRoot(), cpp);

    cpp.close();
}

void gen_Program(Node& node, ofstream& file){
    //cout << "program\n";
    vector<Node> children = node.getChildren();
    file << "#include <iostream>\n";
    file << "#include <string>\n";
    gen_Main(children.at(0), file);
}

void gen_Main(Node& node, ofstream& file){
    //cout << "main\n";
    vector<Node> children = node.getChildren();
    gen_MainDef(children.at(0), file);
    gen_FuncBody(children.at(1), file);
}

void gen_MainDef(Node& node, ofstream& file){
    //cout << "maindef\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
    file << node_to_cpp(children.at(1));
    file << node_to_cpp(children.at(2));
    file << node_to_cpp(children.at(3));
    file << "\n";
}

void gen_FuncBody(Node& node, ofstream& file){
    //cout << "funcbody\n";
    vector<Node> children = node.getChildren();
    gen_Scope(children.at(0), file);
}

void gen_Scope(Node& node, ofstream& file){
    //cout << "scope\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(1));
    file << "\n";
    gen_ScopeBody(children.at(2), file);
    file << node_to_cpp(children.at(3));
    file << "\n";
}

void gen_ScopeBody(Node& node, ofstream& file){
    //cout << "scopebody\n";
    vector<Node> children = node.getChildren();
    gen_Code(children.at(0), file);
}

void gen_Code(Node& node, ofstream& file){
    //cout << "code\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Statement"){
        gen_Statement(children.at(0), file);
    }
    else if(children.at(0).getType() == "Scope"){
        gen_Scope(children.at(0), file);
    }
    gen_Codep(children.at(1), file);
}

void gen_Codep(Node& node, ofstream& file){
    //cout << "code'\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "empty"){
        return;
    }
    else if(children.at(0).getType() == "Code"){
        gen_Code(children.at(0), file);
    }
}

void gen_Statement(Node& node, ofstream& file){
    //cout << "stmt\n";
    vector<Node> children = node.getChildren();
    //cout << "\t" << children.at(0).getValue().type << "\n";
    if(children.at(0).getType() == "IO"){
        gen_IO(children.at(0), file);
    }
    else if(children.at(0).getType() == "Return"){
        gen_Return(children.at(0), file);
    }
    else if(children.at(0).getType() == "Decloration"){
        gen_Decloration(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetVoid"){
        gen_RetVoid(children.at(0), file);
    }
}

void gen_IO(Node& node, ofstream& file){
    //cout << "io\n";
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Output"){
        gen_Output(children.at(0), file);
    }
}

void gen_Return(Node& node, ofstream& file){
    //cout << "ret\n";
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
    file << node_to_cpp(children.at(1));
    file << node_to_cpp(children.at(2));
    file << "\n";
}

void gen_Output(Node& node, ofstream& file){
    //cout << "out\n";
    vector<Node> children = node.getChildren();
    file << "std::cout << ";
    gen_String(children.at(1), file);
    file << node_to_cpp(children.at(2));
    file << "\n";
}

void gen_Decloration(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Mut"){
        gen_Mut(children.at(0), file);
    }
    else if(children.at(0).getType() == "Let"){
        gen_Let(children.at(0), file);
    }
}

void gen_Mut(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Type(children.at(1), file);
    file << node_to_cpp(children.at(2));
    file << node_to_cpp(children.at(3));
    file << node_to_cpp(children.at(4));
    file << node_to_cpp(children.at(5));
    file << "\n";
}

void gen_Let(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();

    //type is internally handles if you declare a "nickname" for a type so dont handle it in cpp file
    if(children.at(0).getMetadataValue() == "type"){
        return;
    }
    file << "const ";
    gen_Type(children.at(0), file);
    file << node_to_cpp(children.at(1));
    file << node_to_cpp(children.at(2));
    gen_Value(children.at(3), file);
    file << node_to_cpp(children.at(4));
    file << "\n";
}

void gen_Type(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "kw_string"){
        file << "std::";
    }
    file << node_to_cpp(children.back());
}

void gen_Value(Node& node, ofstream& file){
     vector<Node> children = node.getChildren();
     if(children.at(0).getType() == "String"){
        gen_String(children.at(0), file);
     }
     else if(children.at(0).getType() == "Expression"){
        gen_Expression(children.at(0), file);
     }
     else if(children.at(0).getType() == "Char"){
        gen_Char(children.at(0), file);
     }
     else if(children.at(0).getType() == "Bool"){
        gen_Bool(children.at(0), file);
     }
     else if(children.at(0).getType() == "Type"){
        gen_Type(children.at(0), file);
     }
}

void gen_String(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "ident" || children.at(0).getType() == "string"){
        file << node_to_cpp(children.at(0));
    }
    else if(children.at(0).getType() == "RetString"){
        gen_RetString(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetT"){
        gen_RetT(children.at(0), file);
    }
}

void gen_Int(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "ident" || children.at(0).getType() == "int"){
        file << node_to_cpp(children.at(0));
    }
    else if(children.at(0).getType() == "RetInt"){
        gen_RetInt(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetT"){
        gen_RetT(children.at(0), file);
    }
}

void gen_Char(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "ident" || children.at(0).getType() == "char"){
        file << node_to_cpp(children.at(0));
    }
    else if(children.at(0).getType() == "RetChar"){
        gen_RetChar(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetT"){
        gen_RetT(children.at(0), file);
    }
}

void gen_Bool(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "ident" || children.at(0).getType() == "bool"){
        file << node_to_cpp(children.at(0));
    }
    else if(children.at(0).getType() == "RetBool"){
        gen_RetBool(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetT"){
        gen_RetT(children.at(0), file);
    }
}

void gen_Float(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "ident" || children.at(0).getType() == "float"){
        file << node_to_cpp(children.at(0));
    }
    else if(children.at(0).getType() == "RetFloat"){
        gen_RetFloat(children.at(0), file);
    }
    else if(children.at(0).getType() == "RetT"){
        gen_RetT(children.at(0), file);
    }
}

void gen_Expression(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Term(children.at(0), file);
    gen_Expressionp(children.at(1), file);
}

void gen_Expressionp(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "empty"){
        return;
    }
    gen_Operator(children.at(0), file);
    gen_Term(children.at(1), file);
    gen_Expressionp(children.at(2), file);
}

void gen_Term(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Factor"){
        gen_Factor(children.at(0), file);
    }
    else{
        file << node_to_cpp(children.at(0));
        gen_Expression(children.at(1), file);
        file << node_to_cpp(children.at(2));
    }
}

void gen_Factor(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Number(children.at(0), file);
}

void gen_Operator(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node_to_cpp(children.at(0));
}

void gen_Number(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    if(children.at(0).getType() == "Int"){
        gen_Int(children.at(0), file);
    }
    else{
        gen_Float(children.at(0), file);
    }
}

void gen_RetString(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Str(children.at(0), file);
}

void gen_RetType(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_TypeOf(children.at(0), file);
}

void gen_RetVoid(Node& node, ofstream& file){
    return;
}

void gen_RetInt(Node& node, ofstream& file){
    return;
}

void gen_RetFloat(Node& node, ofstream& file){
    return;
}

void gen_RetBool(Node& node, ofstream& file){
    return;
}

void gen_RetChar(Node& node, ofstream& file){
    return;
}

void gen_RetT(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    gen_Cast(children.at(0), file);
}

void gen_TypeOf(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << node.getMetadataValue();
}

void gen_Cast(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    file << "static_cast<"; 
    gen_Type(children.at(2), file);
    file << ">(";
    gen_Value(children.at(4), file);
    file << ")"; 
}

void gen_Str(Node& node, ofstream& file){
    vector<Node> children = node.getChildren();
    string node_type = Value_type(children.at(2));
    if(node_type == "type" || node_type == "kw_type"){
        file << "\"";
        gen_Value(children.at(2), file);
        file << "\"";
    }
    else{
        file << "std::to_string(";
        gen_Value(children.at(2), file);
        file << ")";
    }
}
