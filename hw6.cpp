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

    //Main Loop
    while (1){
        cout << "input:";
        getline(cin, input);
        Expression expression;
        expression.set(input);
        expression.display();
        
        do
            {
                //Need to make sure it starts with num or letter
                //Need to make sure that the expression is separated by ; properly
                //Need to make sure that it ends with ;
                if (isdigit(input[0]) || isalpha(input[0])){ //Update this loop later (or make a check method)
                    out = true;
                }
                else{
                    out = false;
                    cout << "Incorrect input. Please input a valid expression." << endl;
                    input.clear();
                    getline(cin, input);
                }
            } while (out == false);



        //cout << "Echo input : in quote " << "\"" << input << "\"" << endl;
        while (1) {
            cout << "action:";
            getline(cin, input2);
            
            
            //cout << "Echo action : in quote " << "\"" << input << "\"" << endl;
            if (input2.size() == 1 && input2[0] == 'q'){ //Done
                return;
            }
            else if (input2.size() == 1 && input2[0] == 'c'){ //Able to add to expression. Need to postfix one at a time though. Need to separate these somehow.
                getline(cin, input);
                expression.addToExpression(input);
                expression.display();

            }
            else if (input2.size() == 1 && input2[0] == 's'){ //Done
                cout << "Starting fresh!" << endl;
                expression.clearWorkingTree();
                break;
            }
            else if(input2.size() == 1 && input2[0] == 'f'){
                cout << "Insert method here to fully parenthesize expression" << endl; //Confused
            }
            else if(input2.size() == 1 && input2[0] == '='){
                cout << "Insert method to actually evaluate each expression" << endl; //Very confused
            }
            else if(input2.size() == 1 && input2[0] == '>'){ //Working
                expression.toInfix();
                expression.displayInfix();
            }
            else if (input2.size() == 1 && input2[0] == '<'){ //Working
                expression.toPostfix();
                expression.displayPostfix();
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

