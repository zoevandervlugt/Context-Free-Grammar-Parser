#include <bits/stdc++.h>
using namespace std;


// @brief Opens a file and returns each line as a vector of strings
// @param Name of file
// @return Vector of strings
vector<string> openFile(string fileName) {
    vector<string> lines;       // To store each line
    ifstream file(fileName);    // Opening the file
    string line;                // Buffer to store lines temporarily
    if(file.is_open()){                 // Go through the file
        while(getline(file, line)){     //Get's each line from the file and stores it in the buffer
            lines.push_back(line);      // If we are not at end of file, add the line to the vector
        }
        file.close();
    } else{
        cout << "File could not be opened" << endl;
    }
    return lines;
}

// @brief Given a string, removes extraneous characters like ',' ' ' '->' and converts to a vector (each name is its own string)
// @param String to be split
// @return String vector containing only the variable and terminal names, in the order given
vector<string> splitString(string s){
    vector<string> strings;     // Stores strings containing only the variable and terminal names
    string current = "";        // Temporarily storing 
    int i = 0;      // Loop variable
    while(i < s.size()) {       // Loop till the end of the input string
        if(s[i] == ','){        // 
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
            if(i == s.size() - 1) {
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
    vector<string> rules;       // Stores the rules
    for(int i = 2; i < content.size() - 1; i++) {       // Loop from the second element (line) till the second last element. 
                                                        // These are the lines with the rules.
        string line = content[i];                       // Store each line of rules
        vector<string> ruleContents = splitString(line);    // Splits the rules up so as to make them of the form S -> AB
        for(int i = 1; i < ruleContents.size(); i++) {      // loop from the second element of ruleContents till the last
            rules.push_back(ruleContents[0] + " -> " + ruleContents[i]);    // Stores each rule (now in form S -> AB)
        }
    }
    return rules;
}

// @brief Finds out if there is a rule from the given varible to the given term
// @param A 2d vector of strings for rules
// @param the variable
// @param the term
// @return True if there is a rule from the given varible to the given term, false otherwise 
bool findRule(vector<vector<string>> rules, string var, string term) {
    // cout << "Looking for rule with " << var << " and " << term << endl;
    for(vector<string> rule: rules){        // For each rule
        if(rule[0] == var) {                // Find the rules for the given varible
            // cout << "rule[0] " << rule[0] << endl;
            if(rule.back() == term){        // Check the last element of rule
                //cout << "Found rule" << endl;
                return true;                // If the last element is the given term, return true
            }
        }
    }
    // cout << "Didn't find rule" << endl;
    return false;       // If rule not found, return false
}

// @brief Finds out if a string is part of the given grammar
// @param the string
// @param a vector of strings for all the grammar variables 
// @param a vector of strings for all the terminals
// @param A 2d vector of strings for rules
// @param the start variable
// @return True if the string is in the language, false otherwise
bool checkLine(string line, vector<string> variables, vector<string> terminals, vector<vector<string>> rules, string startVar){
    // Data structure to represent the grammar: a 2d array of vectors
    vector<string> table[line.length()][line.length()]; // arrays are the size of the input string

    // If the line is empty, accept only if there's a rule where the startVar goes to e
    if(line == "" || line == " "){
        // cout << "Checking empty line" << endl;
        return findRule(rules, startVar, "e");
    }
    
    // Goes through each char of the line
    //Examine each substring of length 1
    for(int i = 0; i < line.length(); i++){
        string b = string() + line[i];      // Turn the current char into a string
        for(string A: variables){           // Go through each variables 
            if(findRule(rules, A, b)){      // Checking whether A -> b is a rule
                table[i][i].push_back(A);   // If yes, place A in table(i,i)
                // cout << "(i,i) = (" << i << ", " << i << ")" << "=";
                // for(string str : table[i][i]){
                //     cout << " " << str;
                // }
                // cout << endl;
            }
        }
    }

    for(int l = 2; l <= line.length(); l++){            //l is the length of the substring
        // cout << "length: " << line.length() << endl;
        for(int i = 0; i <= line.length() - l; i++){    // i is the start position of the substring
            int j = i + l - 1;                          // j is the end position of the substring
            // cout << "i: " << i << endl;
            // cout << "j: " << j << endl;
            for(int k = i; k <= j; k++) {               // k is the split position
                // cout << "k: " << k << endl;
                for(vector<string> rule: rules){        // For each rule 
                    cout << "rule[1] = " << rule[1] << endl;
                    if(rule[1].length() > 1){           // If that rule is of the form A -> BC
                        // Store A, B and C
                        string A = rule[0];             
                        string B = string() + rule[1][0];
                        string C = string() + rule[1][1];
                        cout << "A = " << A << ", B = " << B << ", C = " << C << endl;
                        // If table(i,k) contains B and table(k+1, j) conatains C
                        if((count(table[i][k].begin(), table[i][k].end(), B) > 0) && (count(table[k+1][j].begin(), table[k+1][j].end(), C) > 0)){
                            cout << "pushing back " << A << endl;
                            table[i][j].push_back(A);       // Put A in table(i,j)
                            cout << "table[i][j]= ";
                            for(string str: table[i][j]) {
                                cout << str << " ";
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
    // for(int i = 0; i < line.length(); i++) {
    //     cout << "i = " << i << endl;
    //     for(int j = 0; j < line.length(); j++) {
    //         cout << "j = " << j << endl;
    //         for(string var : table[i][j]) {
    //             cout << "var = " << var << endl;
    //         }
    //     }
    // }
    // Returns true if the start variable is in table(1,n). False otherwise
    cout << "about to return" << endl;
    return find(table[0][line.length() - 1].begin(), table[0][line.length() - 1].end(), startVar) != table[0][line.length() - 1].end();
}

int main(){
    cout << std::boolalpha;

    string grammar; //Stores the grammar file
    string input;   //Stores the input file
    cin >> grammar >> input;    // Take in file names from console

    vector<string> grammarContents = openFile(grammar);     // Turn grammar into a vector of strings, one string per line
    vector<string> rules = readRules(grammarContents);      // Store the rules of the grammar (includes '->')

    cout << "Variables: " << grammarContents[0] << endl << endl;    //Printing out the variables
    cout << "Terminals: " << grammarContents[1] << endl << endl;    //Printing out the terminals
    cout << "Rules: " << endl << "------" << endl;
    for(string rule: rules) {
        cout << rule << endl;   //Printing out each rule
    }
    cout << endl;
    cout << "Start Variable: " << grammarContents.back() << endl;   //Printing out the start variable
    cout << endl;
    vector<string> inputContents = openFile(input);                 // Turn input into a vector of strings, one string per line
    vector<string> variables = splitString(grammarContents[0]);     // Store the formatted version of the first line of the grammar (each variable is a string)
    vector<string> terminals = splitString(grammarContents[1]);     // Store the formatted version of second line of input
    string startVar = grammarContents.back();                       // Set start variable to last line of input
    
    // Format rules by turning them into a vector, where each rule is a vector containing the variable and what it turns into as their own strings
    vector<vector<string>> formattedRules;
    for(string rule: rules){
        formattedRules.push_back(splitString(rule));
    }

    for(vector<string> rule: formattedRules){
        for(string str: rule){
            cout << str << " ";
        }
        cout << endl;
    }

    // Check each line against the grammar using checkline, and print the matching message
    for(string line: inputContents){
        cout << line << endl;
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
// anbnGrammar.txt anbnGrammarInput.txt
// palindromeGrammar.txt palindromeGrammarInput.txt
// equalAsBsGrammar.txt equalAsBsGrammarInput.txt