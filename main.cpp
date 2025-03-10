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

    cout << "Variables: " << contents[0] << endl << endl;
    cout << "Terminals: " << contents[1] << endl << endl;
    cout << "Rules: " << endl << "------" << endl << "*Insert Rules Here*" << endl << endl;
    cout << "Start Variable: " << contents.back() << endl;
}
// astarGrammar.txt astarGrammarInput.txt