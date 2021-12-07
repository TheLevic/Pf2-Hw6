/* 
 * File:   main.cpp
 * Author: Levi Crider
 *
 * Created on November 15, 2021, 4:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "helpers/Expression.h"
#include "helpers/Token.h"
using namespace std;

void interactive(){
    //Declarations
    string input; //Users expressions
    string input2; //Users action
    bool out; //Bool to get correct expression
    Expression expression;
    vector<Expression> expressions; //Able to keep creating expressions

    //Main Loop
    while (1){
        int count = 0;
        cout << "input:";
        getline(cin, input);
        expression.set(input);
        expressions.push_back(expression);
        expressions.at(count).syntaxCheck(); //Does syntax check each time we create a new expression
        do
            {
                //Need to make sure it starts with num or letter
                //Need to make sure that the expression is separated by ; properly
                //Need to make sure that it ends with ;
                if ((isdigit(input[0]) || isalpha(input[0]) ) && input[input.size() - 1] == ';'){ //Update this loop later (or make a check method)
                    out = true;
                }
                else{
                    out = false;
                    cout << "Incorrect input. Please input a valid expression (Make sure you have ; at the end)" << endl;
                    input.clear();
                    getline(cin, input);
                }
            } while (out == false);

        while (1) {
            cout << "action:";
            getline(cin, input2);
            
            if (input2.size() == 1 && input2[0] == 'q'){ //Done
                return;
            }
            else if (input2.size() == 1 && input2[0] == 'c'){ //Done
                cout << "input: ";
                getline(cin, input);
                do
            {
                //Need to make sure it starts with num or letter
                //Need to make sure that the expression is separated by ; properly
                //Need to make sure that it ends with ;
                if ((isdigit(input[0]) || isalpha(input[0]) ) && input[input.size() - 1] == ';'){ //Update this loop later (or make a check method)
                    out = true;
                }
                else{
                    out = false;
                    cout << "Incorrect input. Please input a valid expression (Make sure you have ; at the end)" << endl;
                    input.clear();
                    getline(cin, input);
                }
            } while (out == false);
                expressions.push_back(input);
                count++;
                expressions.at(count).syntaxCheck(); //Perform a syntax check to see what the user's input was
            }
            else if (input2.size() == 1 && input2[0] == 's'){ //Done
                cout << "Starting fresh!" << endl;
                expressions.clear();
                break;
            }
            else if(input2.size() == 1 && input2[0] == 'f'){
                cout << "Insert method here to fully parenthesize expression" << endl; //Confused
            }
            else if(input2.size() == 1 && input2[0] == '='){
                cout << "Insert method to actually evaluate each expression" << endl; //Very confused
            }
            else if(input2.size() == 1 && input2[0] == '>'){ //Working
                for (int i = 0; i < expressions.size(); i++){
                    expressions.at(i).toPrefix();
                    cout << "Prefix of " << expressions.at(i).getoriginal() << " is ";
                    expressions.at(i).displayPrefix();
                    cout << endl;
                }
            }
            else if (input2.size() == 1 && input2[0] == '<'){ //Working
                for (int i = 0; i < expressions.size(); i++){
                    expressions.at(i).toPostfix();
                    cout << "Postfix of " << expressions.at(i).getoriginal() << " is ";
                    expressions.at(i).displayPostfix();
                    cout << endl;
                }
            }
            else{ //Covers all other input possible. Only inputs that will actually run methods are the ones listed above
                cout << "Wrong input for the action! Please type one of =, <, >, f(F), q(Q), c(C), s(S)" << endl;
            }
        }
    }
}


int main(int argc, char** argv) {
    cout << "=== expression evaluation program starts ===" << endl;
    interactive();
    cout << "=== expression evaluation program ends ===" <<  endl;

    return 0;
}

