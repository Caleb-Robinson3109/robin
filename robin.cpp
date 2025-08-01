#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Needs correct number of arguments";
        return 1;
    }

    fstream robin(argv[1]);

    if(!robin){
        cerr << "Cannot open file";
        return 1;
    }

    stringstream buffer;
    buffer << robin.rdbuf();

    string contents = buffer.str();
    cout << contents;

    for(char c : contents){
        if(c == '\n'){
            cout << "\\n";
        }
        cout << c;
    }

    return 0;
}