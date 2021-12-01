/* 
 * File:   main.cpp
 * Author: Levi Crider
 *
 * Created on November 15, 2021, 4:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void interactive(){
    //Declarations
    string input;
    bool out; //Bool to get correct expression

    //Main Loop
    while (1){
        cout << "input:";
        getline(cin, input);
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
            getline(cin, input);
            
            
            //cout << "Echo action : in quote " << "\"" << input << "\"" << endl;
            if (input.size() == 1 && input[0] == 'q'){
                return;
            }
            else if (input.size() == 1 && input[0] == 'c'){
                break;
            }
            else if (input.size() == 1 && input[0] == 's'){
                cout << "Insert method here to clear our working tree" << endl;
            }
            else if(input.size() == 1 && input[0] == 'f'){
                cout << "Insert method here to fully parenthesize expression" << endl;
            }
            else if(input.size() == 1 && input[0] == '='){
                cout << "Insert method to actually evaluate each expression" << endl;
            }
            else if(input.size() == 1 && input[0] == '>'){
                cout << "Insert method here to convert each expression in the sequence of expressions to the equivalent prefix expression" << endl;
            }
            else if (input.size() == 1 && input[0] == '<'){
                cout << "Insert method here to convert each expression in the sequence of expressions to the equivalent postfix expression." << endl;
            }
            else{ //Covers all other input possible. Only inputs that will actually run methods are the ones listed above
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "=== expression evaluation program starts ===" << endl;
    interactive();
    cout << "=== expression evaluation program ends ===" <<  endl;

    return 0;
}

