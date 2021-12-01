#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Token.h"
#include <cstdlib>
#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
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
    
    //Need to evaluate infix expression (human like input)
    void evaluateInfix(vector<Token> a);
    
    
    




private:
    string original;
    vector<Token> tokenized; //Infix
    vector<Token> postfix;
    bool valid;
    Exp_type type;
    stack<Token> stack;
    //int numTokens;


};

#endif /*EXPRESSION_H*/