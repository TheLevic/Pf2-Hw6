#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Token.h"
#include <cstdlib>
#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum Exp_type {Assignment, Arithmetic, Bad};

class Expression{

public:
    //Constructors
    Expression(); //Done
    Expression(const string &s); //Done
    void set(const string& s); //Need to do 
    void display() const; //Done
    string getoriginal() const;  //Done
    vector<Token> get_tokenized() const; //Done




private:
    string original;
    vector<Token> tokenized;
    vector<Token> postfix;
    bool valid;
    Exp_type type;
    //int numTokens;


};

#endif /*EXPRESSION_H*/