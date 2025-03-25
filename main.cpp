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

bool findRule(vector<vector<string>> rules, string var, string term) {
    for(vector<string> rule: rules){
        if(rule[0] == var) {
            if(rule.back() == term){
                return true;
            }
        }
    }
    return false;
}

bool checkLine(string line, vector<string> variables, vector<string> terminals, vector<vector<string>> rules, string startVar){
    string table[line.length() - 1][line.length() - 1];
    if(line == "" || line == " "){
        return findRule(rules, startVar, "e");
    }
    for(int i = 0; i < line.length(); i++){
        string b = line[i] + "";
        for(string A: variables){
            if(findRule(rules, A, b)){
                table[i][i] = A;
            }
        }
    }
    for(int l = 1; l < line.length(); l++){
        for(int i = 0; i < line.length() - l + 1; i++){
            int j = i + l - 1;
            for(int k = i; i <= j - 1; k++) {
                // For each rule that leads to 2 concatenated variables
                
            }
        }
    }
}

int main(){

    string grammar;
    string input;
    
    cin >> grammar >> input;

    vector<string> grammarContents = openFile(grammar);
    
    vector<string> rules = readRules(grammarContents);

    cout << "Variables: " << grammarContents[0] << endl << endl;
    cout << "Terminals: " << grammarContents[1] << endl << endl;
    cout << "Rules: " << endl << "------" << endl;
    for(string rule: rules) {
        cout << rule << endl;
    }

    cout << endl;
    cout << "Start Variable: " << grammarContents.back() << endl;

    vector<string> inputContents = openFile(input);
    vector<string> variables = splitString(grammarContents[0]);
    vector<string> terminals = splitString(grammarContents[1]);
    string startVar = grammarContents.back();

    vector<vector<string>> formattedRules;
    for(string rule: rules){
        formattedRules.push_back(splitString(rule));
    }

    for(string line: inputContents){
        if(checkLine(line, variables, terminals, formattedRules, startVar)){
            cout << line << ": Accept" << endl;
        } else {
            cout << line << ": Reject" << endl;
        }
    }

}
// g++ main.cpp -o main
// ./main
// astarGrammar.txt astarGrammarInput.txt