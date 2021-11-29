#ifndef TOKEN_H
#define TOKEN_H

#include <cstdlib>
#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum Token_type {Identifier, Integer, Operators, EqualSign, OpenBrace, CloseBrace, INVALID};

class Token
{
public:
    //Constructors
    Token();
    Token(string s);

    //member functions
    void set(string s);
    int value() const;
    void display() const;

    //Getters
    Token_type get_type() const;
    string get_token() const;
    int get_priority() const;

private:
    //member variables
    Token_type type; //Stores the type
    string token; //Stores the token
    int priority; //Stores priority of token when it is an operator/parentheses

    //Methods to use for our member functions
    void checkString(string s);
};

#endif /*TOKEN_H*/