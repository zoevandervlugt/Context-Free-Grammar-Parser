# Context-Free-Grammar-Parser [Course Project Description](https://docs.google.com/document/d/1NzWoRt5bRfIU2RMqYrBLgnyAt2gfWIe5aHU6L1U8qQk/edit?usp=sharing)
This repository contains coursework from my Theory of Computation class at Southwestern University. All code is original unless otherwise noted. This code was produced as a collaboration between Zoe Van Der Vlugt and Reeha Rauf. Do not submit this code as your own in any academic setting.

## Objectives
The purpose of this assignment is to get familiar  with designing grammars, and then designing programs that can use a grammar to parse and filter strings. It utilizes the technique of dynamic programming for more efficiency.

Files included:
```
  main.cpp  - Contains the main code
  astarGrammar.txt  - Grammar for L = a*
  anbnGrammar.txt   - Grammar for L = a^nb^n
  palindromeGrammar.txt - Grammar for L = {w | w is a palindrome}
  equalAsBsGrammar.txt  - Grammar for L = {w | w has equal a's and b's}
  astarGrammarInput.txt - Strings for testing astarGrammar.txt
  anbnGrammarInput.txt  - Strings for testing anbnGrammar.txt
  palindromeGrammarInput.txt - Strings for testing palindromeGrammar.txt
  equalAsBsGrammarInput.txt - Strings for testing equalAsBsGrammar.txt
  README.md - Read me
```

## Context-free Grammars ##
Context-free grammar (CFG) consists of the following four parts:
- A set of variables V
- A set of terminals Sigma
- A set of production rules R
- A start variable S

This is an example of a context-free grammar:
```
X → aX | aY 
Y → bbYc | d | 
```
Where,
```
V = {X, B} 
Sigma = {a, b, c, d} 
R = {X -> aX, X → aY, Y → bbYc, Y → d, Y → } 
X is the start variable (this is implied since it is on the left side of the first rule.)
```
## Our Code ##

Our code is written in C++. It takes in two files-one that describes the grammar, and one that has the strings to be checked. 

To compile the code, run the following command
```
g++ main.cpp -o main
```
Then, to run the code
```
./main
```
You can then copy and paste the file names. These are some examples
```
astarGrammar.txt astarGrammarInput.txt
```
```
anbnGrammar.txt anbnGrammarInput.txt
```
```
palindromeGrammar.txt palindromeGrammarInput.txt
```
```
equalAsBsGrammar.txt equalAsBsGrammarInput.txt
```
## Sources ##
- https://www.geeksforgeeks.org/bitsstdc-h-c/
- https://www.geeksforgeeks.org/read-a-file-line-by-line-in-cpp/
- https://www.w3schools.com/cpp/cpp_strings_input.asp
