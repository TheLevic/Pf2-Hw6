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
    int count = 0;
    string input; //Users expressions
    string input2; //Users action
    bool out; //Bool to get correct expression
    vector<Expression> expressions; //Able to keep creating expressions
    //Main Loop
    while (1){
        
        cout << "input:";
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
        expressions.at(count).syntaxCheck(); //Does syntax check each time we create a new expression

        while (1) {
            cout << "action:";
            getline(cin, input2);
            
            if (input2.size() == 1 && input2[0] == 'q'){ //Done
                return;
            }
            else if (input2.size() == 1 && input2[0] == 'c'){ //Done
                count++;
                break;
            }


            else if (input2.size() == 1 && input2[0] == 's'){ //Done
                cout << "Starting fresh!" << endl;
                expressions.clear();
                break;
            }
            else if(input2.size() == 1 && input2[0] == 'f'){
                for (int i = 0; i < expressions.size(); i++){
                    expressions.at(i).toPostfix();
                    expressions.at(i).fullyParenth();
                }
            }
            else if(input2.size() == 1 && input2[0] == '='){

                for (int i = 0; i < expressions.size(); i++){

                    if (expressions.at(i).getType() == Assignment){
                        cout << "I couldn't get it to set variables. Explanation in homework report" << endl;
                    }

                    else if (expressions.at(i).getValid() == true){
                        expressions.at(i).toPostfix();
                        cout << expressions.at(i).getoriginal() << " = ";
                        expressions.at(i).evaluate();
                    }

                    
                    
                    else if (expressions.at(i).getValid() == false){
                        cout << "Can't evaluate BAD expression" << endl;
                    } 
                    
                
                }
                
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

