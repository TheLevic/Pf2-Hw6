#include "Expression.h"
#include "Token.h"


//For ease of use in my methods I created this
bool isSpecial(const string& s, int i){
    if(s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '='){
        return true;
    }
    else{
        return false;
    }
}



Expression::Expression(){
    original = ""; //Making sure original is Empty
    type = Bad; //Setting type to bad
    valid = false; //Setting valid to be false initially
    tokenized.clear(); //Making sure the inital vector is empty
    postfix.clear(); //Making sure the inital vector is empty
}


Expression::Expression(const string& s){
    set(s); //Using the set method
}


void Expression::set(const string& s){
    //We need to separate each character based on the definition of a token (tokens are separated by spaces or special characters);
    //Once the first token is found, add it into tokenized
    //After adding into tokenized, repeat this process from the next position
    //at which we stopped at until finding the terminating NULL character (hence the do while loop)

    string semi = ";";
    original = s; //Setting original
    string tmp; //Temporary string to hold values
    tmp.clear(); //Making sure tmp is clear.
    tokenized.clear(); //Making sure the vector is clear
    int i = 0; //Keeping our place
    do
    {
        
        if (isSpecial(s,i) == false && s[i] != ' ' && s[i] != '\0'){ //If it's an ordinary character
            tmp =  tmp + s[i]; //Setting tmp = to itself + the next char
            i++; //moving on
        }

        if (isSpecial(s,i) == true){
            if (tmp.empty() != true){ //If tmp is not empty
                tokenized.push_back(tmp); //Adding tmp to vector
                tmp.clear(); //Clear tmp
                tmp = s[i]; //Setting tmp = to our char
                tokenized.push_back(tmp); //Adding tmp to our vector
                tmp.clear(); //Clearing tmp
                i++; //Moving on
            }
            else if(tmp.empty() == true){ // if Tmp is empty
                tmp = s[i]; //Setting tmp to our char
                tokenized.push_back(tmp); //Adding to vector
                tmp.clear(); //Clearing tmp
                i++; //Moving on
            }
        }

        if(s[i] == ' '){ //If s is equal to space
            if (tmp.empty() != true){ //And if tmp is not empty
                tokenized.push_back(tmp); //Adding tmp to our vector
                tmp.clear(); //clearing tmp
                i++; //Moving on
            }
            else{ //If it is empty
                i++; //Move on
            }
        }
        if(s[i] == '\0'){ //Once we reach the NULL char
            if (tmp.empty() != true){ //If tmp is not empty
                tokenized.push_back(tmp); //Adding tmp to vector
                tmp.clear(); //Clearing tmp
                break;//Exiting loop
            } 
            else{
                break; //Exiting loop if tmp is empty
            }
        }
    } while (s[i] != '\0');
}



void Expression::display() const{
    string semi = ";";
    cout << "original = " << original << endl;
    cout << "tokenized = ";
    for (int i = 0; i < tokenized.size(); i++){
       cout << tokenized.at(i).get_token() + semi;
    }
    cout << endl;
    cout << "postfix = " << endl;
    cout << "valid = " << valid << endl;
    cout << "type = " << type << endl;
    cout << "----------------------------------------" << endl;
}

string Expression::getoriginal() const{
    return original;
}
vector<Token> Expression::get_tokenized() const{
    return tokenized;
}
