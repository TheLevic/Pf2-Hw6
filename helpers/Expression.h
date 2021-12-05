#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Token.h"
#include <cstdlib>
#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <map>
using namespace std;

enum Exp_type {Assignment, Arithmetic, Bad};

class Expression{

public:
    //Constructors
    Expression(); //Done
    Expression(const string &s); //Done

    //Methods
    void set(const string& s); //Need to do 
    void display() const; //Done
    string getoriginal() const;  //Done
    vector<Token> get_tokenized() const; //Done
    
    void toPostfix();
    void toInfix();
    void clearWorkingTree();
    void displayPostfix();
    void displayInfix();
    void addToExpression(const string input);
    void syntaxCheck(Expression input);
    void evaluateExpression();

private:
    string original;
    vector<Token> tokenized; //Infix
    vector<Token> postfix;
    vector<Token> infix;
    bool valid;
    Exp_type type;
    stack<Token> stack;
    map<Token, Token> mp;
    


};

#endif /*EXPRESSION_H*/