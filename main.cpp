#include <bits/stdc++.h>
using namespace std;

// @brief Opens a file and returns a vector of strings (one for each line)
// @param Name of file
// @return Vector of strings (one for each file line)
vector<string> openFile(string fileName) {
    vector<string> lines;
    ifstream file(fileName);
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

// @brief Given a string, removes extraneous characters like ',' ' ' '->' and converts to a vector (each name is its own string)
// @param String to be split
// @return String vector containing only the variable and terminal names, in the order given
vector<string> splitString(string s){
    vector<string> strings;
    string current = "";
    int i = 0;
    while(i < s.size()) {
        if(s[i] == ','){
            strings.push_back(current);
            current = "";
            i = i+2;
        } else if(s[i] == ' '){
            strings.push_back(current);
            current = "";
            if(s[i+1] == '-'){
                i = i+4;
            } else{
                i = i+3;
            }
        } else{
            current = current + s[i];
            if(s[i] == s.back()) {
                strings.push_back(current);
            }
            i++;
        }
    }
    return strings;
}

// @brief Given the contents of a grammar file, return the rules
// @param String vector of contents of the file
// @return String vector of the rules of the grammar defined in the file
vector<string> readRules(vector<string> content) {
    vector<string> rules;
    for(int i = 2; i < content.size() - 1; i++) {
        string line = content[i];
        vector<string> ruleContents = splitString(line);
        for(int i = 1; i < ruleContents.size(); i++) {
            rules.push_back(ruleContents[0] + " -> " + ruleContents[i]);
        }
    }
    return rules;
}

int main(){
    string grammar;
    string input;
    cin >> grammar >> input;

    // testing file names
    // cout << grammar << " " << input;

    vector<string> contents = openFile(grammar);
    // testing openFile
    // for(string line: contents){
    //     cout << line << endl;
    // }

    vector<string> variables = splitString(contents[0]);
    // testing splitString
    // for(string s: variables){
    //     cout << s << endl;
    // }

    vector<string> rules = readRules(contents);

    cout << "Variables: " << contents[0] << endl << endl;
    cout << "Terminals: " << contents[1] << endl << endl;
    cout << "Rules: " << endl << "------" << endl;
    for(string rule: rules) {
        cout << rule << endl;
    }
    cout << endl;
    cout << "Start Variable: " << contents.back() << endl;
}
// astarGrammar.txt astarGrammarInput.txt