#include <bits/stdc++.h>
using namespace std;

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
    for(string line: contents){
        cout << line << endl;
    }
}