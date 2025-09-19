#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "token.hpp"
#include "ast.hpp"
#include "parser.hpp"
#include "context.hpp"

using namespace std;

static vector<string> scope_context;
static Table variable_table;

bool type_check(Var& var, Token& token){
    if(token.type == "ident"){
        Var v = variable_table.get_value(token.value);
        if(var.type == "kw_int" && v.type == "kw_int"){
            return true;
        }
        else if(var.type == "kw_float" && v.type == "kw_float"){
            return true;
        }
        else if(var.type == "kw_char" && v.type == "kw_char"){
            return true;
        }
        else if(var.type == "kw_bool" && v.type == "kw_bool"){
            return true;
        }
        else if(var.type == "kw_string" && v.type == "kw_string"){
            return true;
        }
        else{
            cerr << var.type << " " << v.type << "\n";
            return false;
        }
    }
    else{
        if(var.type == "kw_int" && token.type == "int"){
            return true;
        }
        else if(var.type == "kw_float" && token.type == "float"){
            return true;
        }
        else if(var.type == "kw_char" && token.type == "char"){
            return true;
        }
        else if(var.type == "kw_bool" && token.type == "bool"){
            return true;
        }
        else if(var.type == "kw_string" && token.type == "string"){
            return true;
        }
        else{
            cerr << var.type << " " << token.type << "\n";
            return false;
        }
    }
}

bool safe_at(int index, vector<Token>& tokens){
    /*if(index >= 0 && index < (static_cast<int>(tokens.size()))){
        cout << tokens.at(index).value << "\n";
    }
    else{
        cout << "!!!!!!!!!!!!!!!!!!!!!!!\n";
    }*/
    return (index >= 0 && index < (static_cast<int>(tokens.size())) ? true : false);
}

AST parser (vector<Token>& tokens){
    //cout << "parser\n";
    int index = 0;
    Ret parsed = parse_Program(tokens, index);
    //parsed.printRet();
    if(parsed.valid){
        Node okay = parsed.ast;
        return AST(okay);
    }
    else{
        Node error("error", Token("error", "", -1, -1), false);
        //Node error("error", tokens.at(index), false);
        return AST(error);
    }
}

Ret parse_Program(vector<Token>& tokens, int index){
    //cout << "program\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Program(Node("Program", {"Program", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Main = parse_Main(tokens, index);
    //parsed_Main.printRet();

    if(!parsed_Main.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    index = parsed_Main.index;
    Program.getRoot().addChild(parsed_Main.ast);

    Ret okay(true, Program.getRoot(), index);
    //okay.printRet();
    return okay;
        
}

Ret parse_Main(vector<Token>& tokens, int index){
    //cout << "main\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Main(Node("Main", {"Main", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_MainDef = parse_MainDef(tokens, index);
    //parsed_MainDef.printRet();
    
    if(!parsed_MainDef.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    index = parsed_MainDef.index;
    Ret parsed_FuncBody = parse_FuncBody(tokens, index);
    Main.getRoot().addChild(parsed_MainDef.ast);
    //parsed_FuncBody.printRet();

    if(!parsed_FuncBody.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Main.getRoot().addChild(parsed_FuncBody.ast);
    //parsed_MainDef.ast.printNode();
    //parsed_FuncBody.ast.printNode();
    index = parsed_FuncBody.index;
    
    Ret okay(true, Main.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_MainDef(vector<Token>& tokens, int index){
    //cout << "def\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST MainDef(Node("MainDef", {"MainDef", "", tokens.at(index).line, tokens.at(index).col}, false));
    
    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_main")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    MainDef.getRoot().addChild(Node("kw_main", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_arrow")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    MainDef.getRoot().addChild(Node("kw_arrow", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_int")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    MainDef.getRoot().addChild(Node("kw_int", tokens.at(index), true));
    index++;

    Ret okay(true, MainDef.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_FuncBody(vector<Token>& tokens, int index){
    //cout << "body\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST FuncBody(Node("FuncBody", {"FuncBody", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Scope = parse_Scope(tokens, index);
    //parsed_Scope.printRet();
    
    if(!parsed_Scope.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    FuncBody.getRoot().addChild(parsed_Scope.ast);
    index = parsed_Scope.index;
    
    Ret okay(true, FuncBody.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Scope(vector<Token>& tokens, int index){
    //cout << "scope\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << tokens.at(index).value << "\n";
    AST Scope(Node("Scope", {"Scope", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_ScopeType = parse_ScopeType(tokens, index);
    //parsed_ScopeType.printRet();
    
    if(!parsed_ScopeType.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << "typev\n";
    Scope.getRoot().addChild(parsed_ScopeType.ast);
    //cout << "typev\n";
    index = parsed_ScopeType.index;
    //cout << "typev\n";
    //cout << tokens.at(index).value << "\n";
    
    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_open_curly")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << "{\n";
    Scope.getRoot().addChild(Node("kw_open_curly", tokens.at(index), true));
    index++;
    variable_table.push_scope();
    Ret parsed_ScopeBody = parse_ScopeBody(tokens, index);
    //parsed_ScopeBody.printRet();

    if(!parsed_ScopeBody.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Scope.getRoot().addChild(parsed_ScopeBody.ast);
    index = parsed_ScopeBody.index;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_close_curly")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    variable_table.pop_scope();
    scope_context.pop_back();
    Scope.getRoot().addChild(Node("kw_close_curly", tokens.at(index), true));
    index++;

    Ret okay(true, Scope.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_ScopeType(vector<Token>& tokens, int index){
    //cout << "scope type\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
    
    //cout << tokens.at(index).value << "\n";
    AST ScopeType(Node("ScopeType", {"ScopeType", "", tokens.at(index).line, tokens.at(index).col}, false));
    ////cout << tokens.at(index).value << "\n";
    
    if(tokens.at(index).type == "kw_Pure"){
        scope_context.push_back("Pure");
        ScopeType.getRoot().addChild(Node("kw_Pure", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(tokens.at(index).type == "kw_IO"){
        if(find(scope_context.begin(), scope_context.end(), "Pure") != scope_context.end()){
            cerr << "error on line: " << tokens.at(index).line << " column: " << tokens.at(index).line << "\n";
            cerr << "cannot open an IO scope in a Pure scope\n";
            exit(1);
        }
        scope_context.push_back("IO");
        ScopeType.getRoot().addChild(Node("kw_IO", tokens.at(index), true));
        //cout << "index: " << index << "\n";
        index++;
        //cout << "index: " << index << "\n";
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(tokens.at(index).type == "kw_State"){
        if(find(scope_context.begin(), scope_context.end(), "Pure") != scope_context.end()){
            cerr << "error on line: " << tokens.at(index).line << " column: " << tokens.at(index).line << "\n";
            cerr << "cannot open a State scope in a Pure scope\n";
            exit(1);
        }
        scope_context.push_back("State");
        ScopeType.getRoot().addChild(Node("kw_State", tokens.at(index), true));
        index++;
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        scope_context.push_back("empty");
        //cout << "dddddd\n";
        ScopeType.getRoot().addChild(Node("empty", {"empty", "", tokens.at(index).line, tokens.at(index).col}, true));
        Ret okay(true, ScopeType.getRoot(), index);
        //okay.printRet();
        return okay;
    }
}

Ret parse_ScopeBody(vector<Token>& tokens, int index){
    //cout << "sbody\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST ScopeBody(Node("ScopeBody", {"ScopeBody", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Code = parse_Code(tokens, index);
    //parsed_Code.printRet();
    if(!parsed_Code.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    ScopeBody.getRoot().addChild(parsed_Code.ast);
    index = parsed_Code.index;
    
    Ret okay(true, ScopeBody.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Code(vector<Token>& tokens, int index){
    //cout << "code\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Code(Node("Code", {"Code", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Statement = parse_Statement(tokens, index);
    //parsed_Statement.printRet();
    Ret parsed_Scope = parse_Scope(tokens, index);
    //parsed_Scope.printRet();
    if(parsed_Statement.valid){
        Code.getRoot().addChild(parsed_Statement.ast);
        index = parsed_Statement.index;
        Ret parsed_Codep = parse_Codep(tokens, index);
        //parsed_Codep.printRet();
        if(!parsed_Codep.valid){
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }

        Code.getRoot().addChild(parsed_Codep.ast);
        index = parsed_Codep.index;
        
        Ret okay(true, Code.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(parsed_Scope.valid){
        Code.getRoot().addChild(parsed_Scope.ast);
        index = parsed_Scope.index;
        Ret parsed_Codep = parse_Codep(tokens, index);
        //parsed_Codep.printRet();
        if(!parsed_Codep.valid){
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }

        Code.getRoot().addChild(parsed_Codep.ast);
        index = parsed_Codep.index;
        
        Ret okay(true, Code.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Codep(vector<Token>& tokens, int index){
    //cout << "code'\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Code(Node("Code'", {"Code'", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Code = parse_Code(tokens, index);
    //parsed_Code.printRet();
    
    if(!parsed_Code.valid){
        Code.getRoot().addChild(Node("empty", {"empty", "", tokens.at(index).line, tokens.at(index).col}, true));
        Ret okay(true, Code.getRoot(), index);
        //okay.printRet();
        return okay;
    }

    Code.getRoot().addChild(parsed_Code.ast);
    index = parsed_Code.index;

    Ret okay(true, Code.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Statement(vector<Token>& tokens, int index){
    //cout << "stmt\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Statement(Node("Statement", {"Statement", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_IO = parse_IO(tokens, index);
    //parsed_IO.printRet();
    Ret parsed_Return = parse_Return(tokens, index);
    //parsed_Return.printRet();
    //cout << "parsing Delc\n";
    Ret parsed_Delcoration = parse_Decloration(tokens, index);
    if(parsed_IO.valid){
        if(!(find(scope_context.begin(), scope_context.end(), "IO") != scope_context.end())){
            cerr << "error on line: " << tokens.at(index).line << " column: " << tokens.at(index).line << "\n";
            cerr << "must be in an IO scope to preform IO actions\n";
            exit(1);
        }
        Statement.getRoot().addChild(parsed_IO.ast);
        index = parsed_IO.index;
        Ret okay(true, Statement.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(parsed_Return.valid){
        Statement.getRoot().addChild(parsed_Return.ast);
        index = parsed_Return.index;
        Ret okay(true, Statement.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(parsed_Delcoration.valid){
        Statement.getRoot().addChild(parsed_Delcoration.ast);
        index = parsed_Delcoration.index;
        Ret okay(true, Statement.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_IO(vector<Token>& tokens, int index){
    //cout << "io\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST IO(Node("IO", {"IO", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Output = parse_Output(tokens, index);
    //parsed_Output.printRet();

    if(!parsed_Output.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    IO.getRoot().addChild(parsed_Output.ast);
    index = parsed_Output.index;

    Ret okay(true, IO.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Return(vector<Token>& tokens, int index){
    //cout << "ret\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Return(Node("Return", {"Return", "", tokens.at(index).line, tokens.at(index).col}, false));
    
    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_return")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Return.getRoot().addChild(Node("kw_return", tokens.at(index), true));
    index++;
    //TODO expand return for more values not just 0

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "int")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Return.getRoot().addChild(Node("int", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_semicolon")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Return.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
    index++;

    Ret okay(true, Return.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Output(vector<Token>& tokens, int index){
    //cout << "out\n";

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //tokens.at(index).print_token_struct();
    //tokens.at(index + 1).print_token_struct();
    //tokens.at(index+ 2).print_token_struct();
    //tokens.at(index+ 3).print_token_struct();
    AST Output(Node("Output", {"Output", "", tokens.at(index).line, tokens.at(index).col}, false));

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_output")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Output.getRoot().addChild(Node("kw_output", tokens.at(index), true));
    index++;
    //TODO expand output for more strings/ string concats not just string
    Ret parsed_Value = parse_Value(tokens, index);

    if(!parsed_Value.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Output.getRoot().addChild(parsed_Value.ast);
    index = parsed_Value.index;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_semicolon")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Output.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
    index++;

    Ret okay(true, Output.getRoot(), index);
    //okay.printRet();
    return okay;
}

Ret parse_Decloration(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Decloration(Node("Decloration", {"Decloration", "", tokens.at(index).line, tokens.at(index).col}, false));
    //cout << "parsing mut\n";
    Ret parsed_Mut = parse_Mut(tokens, index);
    //cout << "parsing mut\n";
    Ret parsed_Let = parse_Let(tokens, index);
    if(parsed_Mut.valid){
        if(find(scope_context.begin(), scope_context.end(), "Pure") != scope_context.end()){
            cerr << "error on line: " << tokens.at(index).line << " column: " << tokens.at(index).line << "\n";
            cerr << "declaring a mutable value in a Pure scope\n";
            exit(1);
        }
        Decloration.getRoot().addChild(parsed_Mut.ast);
        index = parsed_Mut.index;
        Ret okay(true, Decloration.getRoot(), index);
        return okay;
    }
    else if(parsed_Let.valid){
        //cout << "parsed let\n";
        Decloration.getRoot().addChild(parsed_Let.ast);
        index = parsed_Let.index;
        Ret okay(true, Decloration.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Mut(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Mut(Node("Mut", {"Mut", "", tokens.at(index).line, tokens.at(index).col}, false));
    Var newVar;
    newVar.line = tokens.at(index).line;
    newVar.col = tokens.at(index).col;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_mut")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Mut.getRoot().addChild(Node("kw_mut", tokens.at(index), true));
    newVar.mut = true;
    index++;
    Ret parsed_Type = parse_Type(tokens, index);

    if(!parsed_Type.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    newVar.type = parsed_Type.ast.getChildren().at(0).getType();
    Mut.getRoot().addChild(parsed_Type.ast);
    index = parsed_Type.index;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "ident")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    newVar.name = tokens.at(index).value;
    Mut.getRoot().addChild(Node("idnet", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_equal")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Mut.getRoot().addChild(Node("kw_equal", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "int")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    if(!type_check(newVar, tokens.at(index))){
        cerr << "error at line: " << tokens.at(index).line << " column: " << tokens.at(index).col << "\n";
        cerr << "type defination mismatch\n";
        exit(1);
    }

    newVar.value = tokens.at(index).value;
    Mut.getRoot().addChild(Node("int", tokens.at(index), true));
    index++;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_semicolon")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Mut.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
    index++;

    Ret okay(true, Mut.getRoot(), index);
    variable_table.add_var(newVar);
    //variable_table.print_table();
    return okay;
}

Ret parse_Let(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Let(Node("Let", {"Let", "", tokens.at(index).line, tokens.at(index).col}, false));
    //cout << "parsing type\n";
    Ret parsed_Type = parse_Type(tokens, index);
    Var newVar;
    newVar.line = tokens.at(index).line;
    newVar.col = tokens.at(index).col;
    newVar.mut = false;

    if(!parsed_Type.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    newVar.type = parsed_Type.ast.getChildren().at(0).getType();
    //cout << "parsed type\n";
    Let.getRoot().addChild(parsed_Type.ast);
    index = parsed_Type.index;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "ident")){
       Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error; 
    }

    newVar.name = tokens.at(index).value;
    //cout << tokens.at(index).value << "\n";
    Let.getRoot().addChild(Node("idnet", tokens.at(index), true));
    index++;
    //cout << parsed_Type.ast.getValue().value << "\n";

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_equal")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << tokens.at(index).value << "\n";
    Let.getRoot().addChild(Node("kw_equal", tokens.at(index), true));
    index++;
    Ret parsed_Value = parse_Value(tokens, index);

    if(!parsed_Value.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    if(!type_check(newVar, tokens.at(index))){
            cerr << "error at line: " << tokens.at(index).line << " column: " << tokens.at(index).col << "\n";
            cerr << "type defination mismatch\n";
            exit(1);
    }

    newVar.value = tokens.at(index).value;
    //cout << tokens.at(index).value << "\n";
    Let.getRoot().addChild(parsed_Value.ast);
    index = parsed_Value.index;

    if(!(safe_at(index, tokens)) || !(tokens.at(index).type == "kw_semicolon")){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << tokens.at(index).value << "\n";
    Let.getRoot().addChild(Node("kw_semicolon", tokens.at(index), true));
    index++;

    Ret okay(true, Let.getRoot(), index);
    variable_table.add_var(newVar);
    //okay.printRet();
    return okay;
}

Ret parse_Type(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Type(Node("Type", {"Type", "", tokens.at(index).line, tokens.at(index).col}, false));

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    if(tokens.at(index).type == "kw_int"){
        Type.getRoot().addChild(Node("kw_int", tokens.at(index), true));
        index++;
        Ret okay(true, Type.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_char"){
        Type.getRoot().addChild(Node("kw_char", tokens.at(index), true));
        index++;
        Ret okay(true, Type.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_string"){
        Type.getRoot().addChild(Node("kw_string", tokens.at(index), true));
        index++;
        Ret okay(true, Type.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_bool"){
        Type.getRoot().addChild(Node("kw_bool", tokens.at(index), true));
        index++;
        Ret okay(true, Type.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_float"){
        Type.getRoot().addChild(Node("kw_float", tokens.at(index), true));
        index++;
        Ret okay(true, Type.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Value(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << "parse value\n";
    AST Value(Node("Value", {"Value", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_String = parse_String(tokens, index);
    Ret parsed_Char = parse_Char(tokens, index);
    Ret parsed_Bool = parse_Bool(tokens, index);
    Ret parsed_Expression = parse_Expression(tokens, index);

    if(parsed_String.valid){
        Value.getRoot().addChild(parsed_String.ast);
        index = parsed_String.index;
        Ret okay(true, Value.getRoot(), index);
        return okay;
    }
    else if(parsed_Expression.valid){
        Value.getRoot().addChild(parsed_Expression.ast);
        index = parsed_Expression.index;
        Ret okay(true, Value.getRoot(), index);
        return okay;
    }
    else if(parsed_Char.valid){
        Value.getRoot().addChild(parsed_Char.ast);
        index = parsed_Char.index;
        Ret okay(true, Value.getRoot(), index);
        return okay;
    }
    else if(parsed_Bool.valid){
        Value.getRoot().addChild(parsed_Bool.ast);
        index = parsed_Bool.index;
        Ret okay(true, Value.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_String(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST String(Node("String", {"String", "", tokens.at(index).line, tokens.at(index).col}, false));
    //cout << "parse string " << tokens.at(index).value << "\n";
    if(tokens.at(index).type == "string"){
        //cout << "type string\n";
        String.getRoot().addChild(Node("string", tokens.at(index), true));
        index++;
        Ret okay(true, String.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "ident"){
        //cout << "str ident\n";
        //cout << tokens.at(index).value << "\n";
        string name = tokens.at(index).value;
        Var v = variable_table.get_value(name);
        
        //cout << "hi\n";
        if(v.type == "kw_string"){
            String.getRoot().addChild(Node("ident", tokens.at(index), true));
            index++;
            Ret okay(true, String.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            //cout << "str error\n";
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        //cout << "str error\n";
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Int(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    //cout << "parse int " << tokens.at(index).value << "\n";
    AST Int(Node("Int", {"Int", "", tokens.at(index).line, tokens.at(index).col}, false));
    
    if(tokens.at(index).type == "ident"){
        //cout << "int varrrrr\n";
        //variable_table.get_value(tokens.at(index).value).print_var();
    }
    if(tokens.at(index).type == "int"){
        Int.getRoot().addChild(Node("int", tokens.at(index), true));
        index++;
        Ret okay(true, Int.getRoot(), index);
        //okay.printRet();
        return okay;
    }
    else if(tokens.at(index).type == "ident"){
        Var v = variable_table.get_value(tokens.at(index).value);
        if(v.type == "kw_int"){
            Int.getRoot().addChild(Node("ident", tokens.at(index), true));
            index++;
            Ret okay(true, Int.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            //cout << v.type << " int error\n";
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        //cout << "int error\n";
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Char(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Char(Node("Char", {"Char", "", tokens.at(index).line, tokens.at(index).col}, false));
    if(tokens.at(index).type == "char"){
        Char.getRoot().addChild(Node("char", tokens.at(index), true));
        index++;
        Ret okay(true, Char.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "ident"){
        Var v = variable_table.get_value(tokens.at(index).value);
        if(v.type == "kw_char"){
            Char.getRoot().addChild(Node("ident", tokens.at(index), true));
            index++;
            Ret okay(true, Char.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            //cout << "char error\n";
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Bool(vector<Token>& tokens, int index){

    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Bool(Node("Bool", {"Bool", "", tokens.at(index).line, tokens.at(index).col}, false));
    if(tokens.at(index).type == "bool"){
        Bool.getRoot().addChild(Node("bool", tokens.at(index), true));
        index++;
        Ret okay(true, Bool.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "ident"){
        Var v = variable_table.get_value(tokens.at(index).value);
        if(v.type == "kw_bool"){
            Bool.getRoot().addChild(Node("ident", tokens.at(index), true));
            index++;
            Ret okay(true, Bool.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            //cout << "bool error\n";
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Float(vector<Token>& tokens, int index){

    if(safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Float(Node("Float", {"Float", "", tokens.at(index).line, tokens.at(index).col}, false));
    if(tokens.at(index).type == "float"){
        Float.getRoot().addChild(Node("float", tokens.at(index), true));
        index++;
        Ret okay(true, Float.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "ident"){
        Var v = variable_table.get_value(tokens.at(index).value);
        if(v.type == "kw_float"){
            Float.getRoot().addChild(Node("ident", tokens.at(index), true));
            index++;
            Ret okay(true, Float.getRoot(), index);
            //okay.printRet();
            return okay;
        }
        else{
            //cout << "float error\n";
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Expression(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Expression(Node("Expression", {"Expression", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Term = parse_Term(tokens, index);

    if(!parsed_Term.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Expression.getRoot().addChild(parsed_Term.ast);
    index = parsed_Term.index;
    Ret parsed_Expressionp = parse_Expressionp(tokens, index);

    if(!parsed_Expressionp.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Expression.getRoot().addChild(parsed_Expressionp.ast);
    index = parsed_Expressionp.index;

    Ret okay(true, Expression.getRoot(), index);
    return okay;
}

Ret parse_Expressionp(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Expressionp(Node("Expression'", {"Expression'", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_operator = parse_Operator(tokens, index);

    if(!parsed_operator.valid){
        Expressionp.getRoot().addChild(Node("empty", {"empty", "", tokens.at(index).line, tokens.at(index).col}, true));
        Ret okay(true, Expressionp.getRoot(), index);
        //okay.printRet();
        return okay; 
    }

    Expressionp.getRoot().addChild(parsed_operator.ast);
    index = parsed_operator.index;
    Ret parsed_Term = parse_Term(tokens, index);

    if(!parsed_Term.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Expressionp.getRoot().addChild(parsed_Term.ast);
    index = parsed_Term.index;
    Ret parsed_expressionp = parse_Expressionp(tokens, index);

    if(!parsed_expressionp.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    Expressionp.getRoot().addChild(parsed_expressionp.ast);
    index = parsed_expressionp.index;
    Ret okay(true, Expressionp.getRoot(), index);
    return okay;
}

Ret parse_Term(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Term(Node("Term", {"Term", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Factor = parse_Factor(tokens, index);

    if(safe_at(index, tokens) && tokens.at(index).type == "kw_open_peren"){
        Term.getRoot().addChild(Node("kw_open_peren", tokens.at(index), true));
        index++;
        Ret parsed_Expression = parse_Expression(tokens, index);

        if(!parsed_Expression.valid){
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error; 
        }

        Term.getRoot().addChild(parsed_Expression.ast);
        index = parsed_Expression.index;

        if(tokens.at(index).type != "kw_close_peren"){
            Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
            //error.printRet();
            return error;
        }

        Term.getRoot().addChild(Node("kw_close_peren", tokens.at(index), true));
        index++;
        Ret okay(true, Term.getRoot(), index);
        return okay;       
    }

    else if(parsed_Factor.valid){
        Term.getRoot().addChild(parsed_Factor.ast);
        index = parsed_Factor.index;

        Ret okay(true, Term.getRoot(), index);
        return okay;
    }

    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Factor(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Factor(Node("Factor", {"Factor", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Number = parse_Number(tokens, index);

    if(!parsed_Number.valid){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error; 
    }

    Factor.getRoot().addChild(parsed_Number.ast);
    index = parsed_Number.index;

    Ret okay(true, Factor.getRoot(), index);
    return okay;
}

Ret parse_Operator(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Operator(Node("Operator", {"Operator", "", tokens.at(index).line, tokens.at(index).col}, false));
    
    if(tokens.at(index).type == "kw_plus"){
        Operator.getRoot().addChild(Node("kw_plus", tokens.at(index), true));
        index++;
        Ret okay(true, Operator.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_minus"){
        Operator.getRoot().addChild(Node("kw_minus", tokens.at(index), true));
        index++;
        Ret okay(true, Operator.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_multiply"){
        Operator.getRoot().addChild(Node("kw_multiply", tokens.at(index), true));
        index++;
        Ret okay(true, Operator.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_mod"){
        Operator.getRoot().addChild(Node("kw_mod", tokens.at(index), true));
        index++;
        Ret okay(true, Operator.getRoot(), index);
        return okay;
    }
    else if(tokens.at(index).type == "kw_divide"){
        Operator.getRoot().addChild(Node("kw_divide", tokens.at(index), true));
        index++;
        Ret okay(true, Operator.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}

Ret parse_Number(vector<Token>& tokens, int index){
    if(!safe_at(index, tokens)){
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }

    AST Number(Node("Number", {"Number", "", tokens.at(index).line, tokens.at(index).col}, false));
    Ret parsed_Int = parse_Int(tokens, index);
    Ret parsed_Float = parse_Float(tokens, index);

    if(parsed_Int.valid){
        Number.getRoot().addChild(parsed_Int.ast);
        index = parsed_Int.index;
        Ret okay(true, Number.getRoot(), index);
        return okay;
    }
    else if(parsed_Float.valid){
        Number.getRoot().addChild(parsed_Float.ast);
        index = parsed_Float.index;
        Ret okay(true, Number.getRoot(), index);
        return okay;
    }
    else{
        Ret error(false, Node("error", Token("error", "", -1, -1), false), index);
        //error.printRet();
        return error;
    }
}