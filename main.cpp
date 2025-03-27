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
    // cout << "Looking for rule with " << var << " and " << term << endl;
    for(vector<string> rule: rules){
        if(rule[0] == var) {
            // cout << "rule[0] " << rule[0] << endl;
            if(rule.back() == term){
                //cout << "Found rule" << endl;
                return true;
            }
        }
    }
    // cout << "Didn't find rule" << endl;
    return false;
}

bool checkLine(string line, vector<string> variables, vector<string> terminals, vector<vector<string>> rules, string startVar){
    // If the line is empty, accept only if there's a rule where the startVar goes to e
    vector<string> table[line.length()][line.length()];
    if(line == "" || line == " "){
        // cout << "Checking empty line" << endl;
        return findRule(rules, startVar, "e");
    }
    
    // Goes through each char of the line
    for(int i = 0; i < line.length(); i++){
        string b = string() + line[i];       // Turn the current char into a string
        for(string A: variables){
            if(findRule(rules, A, b)){
                table[i][i].push_back(A);
                // cout << "(i,i) = " << table[i][i] << endl;
            }
        }
    }

    for(int l = 1; l < line.length(); l++){
        // cout << "length: " << line.length() << endl;
        for(int i = 0; i < line.length() - l; i++){
            
            int j = i + l - 1;
            // cout << "i: " << i << endl;
            // cout << "j: " << j << endl;
            for(int k = i; k <= j; k++) {
                // cout << "k: " << k << endl;// For each rule that leads to 2 concatenated variables
                for(vector<string> rule: rules){
                    if(rule[1].length() > 1){
                        string A = rule[0];
                        string B = string() + rule[0][0];
                        string C = string() + rule[0][1];
                        if((count(table[i][k].begin(), table[i][k].end(), B) > 0) && (count(table[i][k].begin(), table[i][k].end(), C) > 0)){
                            table[i][j].push_back(A);
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < line.length(); i++) {
        cout << "i = " << i << endl;
        for(int j = 0; j < line.length(); j++) {
            cout << "j = " << j << endl;
            for(string var : table[i][j]) {
                cout << "var = " << var << endl;
            }
        }
    }
    return find(table[0][line.length() - 1].begin(), table[0][line.length() - 1].end(), startVar) != table[0][line.length() - 1].end();
}

int main(){
    cout << std::boolalpha;

    string grammar;
    string input;
    cin >> grammar >> input;    // Take in file names

    vector<string> grammarContents = openFile(grammar);             // Turn grammar into a vector of strings, one string per line
    vector<string> rules = readRules(grammarContents);              // Set rules to the rules of the grammar (includes '->')

    cout << "Variables: " << grammarContents[0] << endl << endl;
    cout << "Terminals: " << grammarContents[1] << endl << endl;
    cout << "Rules: " << endl << "------" << endl;
    for(string rule: rules) {
        cout << rule << endl;
    }
    cout << endl;
    cout << "Start Variable: " << grammarContents.back() << endl;
    cout << endl;
    vector<string> inputContents = openFile(input);                 // Turn input into a vector of strings, one string per line
    vector<string> variables = splitString(grammarContents[0]);     // Set variables to a formatted version of the first line of the grammar (each variable is a string)
    vector<string> terminals = splitString(grammarContents[1]);     // Set variables into a formtted version of second line of input
    string startVar = grammarContents.back();                       // Set start variable to last line of input
    
    // Format rules by turning them into a vector, where each rule is a vector containing the variable and what it turns into as their own strings
    vector<vector<string>> formattedRules;
    for(string rule: rules){
        formattedRules.push_back(splitString(rule));
    }

    // Check each line against the grammar using checkline, and print the matching message
    for(string line: inputContents){
        // cout << line << endl;
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