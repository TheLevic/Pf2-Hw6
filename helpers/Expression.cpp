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
	cout << "postfix = " << endl;
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
