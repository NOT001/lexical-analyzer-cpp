#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

string ReadTextFile() {
    string filePath = "./File/Input.txt";
    string code;
    string line;
    ifstream file(filePath);

    if (file.is_open()) {
        while (getline(file, line)) {
            code += line + "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }

    return code;
}

void analyzeCode(string code) {
    string keyword = "while|if|else|return|break|continue|int|float|void|for";

    string letter = "[A-Za-z]";
    string digit = "[0-9]";
    string underscore = "_";
    string identifier = letter + "(" + letter + "|" + digit + "|" + underscore + ")*";

    string digits = digit + "(" + digit + ")*";
    string optionalFraction = "(.(" + digits + "))?";
    string optionalExponent = "(E[+-]?" + digits + ")?";
    string num = digits + optionalFraction + optionalExponent;

    regex keywordPattern("\\b(" + keyword + ")\\b");
    regex identifierPattern("\\b" + identifier + "\\b");
    regex numPattern("\\b" + num + "\\b");
    regex operatorPattern("[-+*/=(){}<>;]");
    regex errorPattern("[.^a-zA-Z_0-9-*/=(){}<>;]");

    vector<string> lexemes;

    regex ws("\\s");
    code = regex_replace(code, ws, " ");
    
    regex op("(\\b|\\s*)([-+*/=(){}<>;])(\\b|\\s*)");
    code = regex_replace(code, op, "$1 $2 $3");

    stringstream ss(code);
    string token;
    
    while (ss >> token) {
        if (regex_match(token, keywordPattern)) {
            lexemes.push_back("keyword : " + token);
        } else if (regex_match(token, identifierPattern)) {
            lexemes.push_back("identifier : " + token);
        } else if (regex_match(token, numPattern)) {
            lexemes.push_back("num : " + token);
        } else if (regex_match(token, operatorPattern)) {
            lexemes.push_back(token + " : " + token);
        } else if (regex_search(token, errorPattern)) {
            lexemes.push_back("Error : " + token);
        }
    }

    cout << "Class : Lexeme" << endl;
    
    for (string lexeme : lexemes) {
        cout << lexeme << endl;
    }
}

int main() {
    string code = ReadTextFile();
    
    cout << code << endl;
    
    analyzeCode(code);

    return 0;
}

