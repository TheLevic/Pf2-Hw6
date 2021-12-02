#include "Expression.h"
#include "Token.h"


Expression::Expression()
{
	original = "";
	valid = false;
	type = Bad;
}

Expression::Expression(const string& s)
{
	set(s);
}

void Expression::set(const string& s)
{
	original = s;
	tokenized.clear();
	string track = "";
	string space = " ";
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == ' '){
			if(!track.empty())
			{
				tokenized.push_back(Token(track));
				track = "";
			}
		}
		else if((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/') || (s[i] == '(') || (s[i] == ')') || (s[i] == '=')){
			if(!track.empty()) {
				tokenized.push_back(Token(track));
				track = "";
			}
			track += s[i];
			tokenized.push_back(Token(track));
			track = "";
		}
		else
		{
			track += s[i];
		}

	}
	if(track != "")
		tokenized.push_back(Token(track));

	valid = false;
	type = Bad;
}

void Expression::display() const
{
	cout << "original = " << original << endl;
	cout << "tokenized = ";
	for(int i = 0; i < tokenized.size(); i++) {
		cout << tokenized.at(i).get_token() << ";";
	}
	cout << endl;
	cout << "number of tokens = " << tokenized.size() << endl;
	cout << "postfix = ";
	cout << endl;
	string validName;
	if(valid==false)
		validName = "false";
	else
		validName = "true";
	cout << "valid = " << validName << endl;
	string nameType;
	switch(type) {
		case 0:
			nameType = "Assignment";
			break;
		case 1: 
			nameType = "Arithmetic";
			break;
		case 2:
			nameType = "Bad";
			break;
		default:
			nameType = "Invalid";
	}
	cout << "type = " << nameType << endl;
}

string Expression::getoriginal() const
{
	return original;
}

vector<Token> Expression::get_tokenized() const
{
	return tokenized;
}

void Expression::evaluateInfix(vector<Token> a){
	//Need to get the first int, then the operator, and then the second int.
	
}

vector<Token> Expression::ToPostfix(){ //Not completely working yet
	for (int i = 0; i < tokenized.size(); i++){
		if (tokenized.at(i).get_type() == Identifier || tokenized.at(i).get_type() == Integer){
			postfix.push_back(tokenized.at(i).get_token());
		}
		else if (tokenized.at(i).get_type() == OpenBrace){
			stack.push(tokenized.at(i).get_token());
		}
		else if (tokenized.at(i).get_type() == CloseBrace){
			while (stack.top().get_type() != OpenBrace){
				postfix.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
		}
		else{ //Operators
			int i = 0;
			while (!stack.empty() && stack.top().get_priority() >= tokenized.at(i).get_priority()){
				postfix.push_back(stack.top());
				stack.pop();
				++i;
			}
			stack.push(tokenized.at(i));
		}
		while (!stack.empty()){
			postfix.push_back(stack.top());
			stack.pop();
		}
	}
	return postfix;
}

void Expression::displayPostfix(){
	for (int i = 0; i < postfix.size(); i++){
		cout << postfix.at(i).get_token();
	}
}

void Expression::clearWorkingTree(){
	tokenized.clear();
	original.clear();
	postfix.clear();
}
