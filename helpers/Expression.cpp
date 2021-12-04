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

void Expression::toPostfix(){ //Not completely working yet
	for (int i = 0; i < tokenized.size() - 1; i++){ //For each token in tokenized
		if (tokenized.at(i).get_type() == Identifier || tokenized.at(i).get_type() == Integer){
			postfix.push_back(tokenized.at(i).get_token());
		}
		else if (tokenized.at(i).get_type() == OpenBrace){
			stack.push(tokenized.at(i));
		}
		else if (tokenized.at(i).get_type() == CloseBrace){
			while (stack.top().get_type() != OpenBrace){
				postfix.push_back(stack.top());
				stack.pop();
			}
			stack.pop(); //Gets rid of the openbrace
		}
		else{ //Operator case
			while (!stack.empty() && stack.top().get_priority() >= tokenized.at(i).get_priority()){
				postfix.push_back(stack.top());
				stack.pop();
			}
			stack.push(tokenized.at(i).get_token());
		}
	}
	while (!stack.empty()){
		postfix.push_back(stack.top());
		stack.pop();
	}

}


void Expression::displayPostfix(){
	cout << "Your postfix expression is: ";
	for (int i = 0; i < postfix.size(); i++){
		cout << postfix.at(i).get_token();
	}
	cout << endl;
}

void Expression::clearWorkingTree(){
	tokenized.clear();
	original.clear();
	postfix.clear();
}
