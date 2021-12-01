#include "Token.h"

Token::Token()
{
	type = INVALID;
	token = "";
	priority = -1;
}

Token::Token(string s)
{
	set(s);
}

void Token::set(string s)
{
	// takes in a string and treats it as a token
	token = s;
	
	// s is empty
	if(s.empty()){
		type = INVALID;
		priority = -1;
	}
	// check if s is an identifier
	else if(isalpha(s[0])){
		bool ident = true;
		for(int i = 1; i < s.length(); i++){
			if(isalnum(s[i]))
				continue;
			else {
				ident = false;
				break;
			}
		}
		if(ident)
			type = Identifier;
		else
			type = INVALID;
		priority = -1;
	}
	// check if s an integer
	else if(isdigit(s[0])) {
		if(s.length() == 1) {
			type = Integer;
			priority = -1;
		}
		else if((s.length() > 1) && (s[0] != '0')) {
			bool number = true;
			for (int i = 0; i < s.length(); i++){
				if(isdigit(s[i]))
					continue;
				else {
					number = false;
					break;
				}
			}
			if(number)
				type = Integer;
			else
				type = INVALID;
			priority = -1;
		}
		else
			return;
	}

	// check if s is an operator
	else if( (s == "+") || (s == "-") || (s == "*") || (s == "/")) {
		type = Operators;
		if(s == "+" || s == "-")
			priority = 1;
		else
			priority = 2;
	}
	// check if s is =
	else if(s == "="){
		type = EqualSign;
		priority = -1;
	}
	// check if s is openbrace
	else if(s == "("){
		type = OpenBrace;
		priority = 0;
	}
	// check if s is closebrace
	else if(s == ")"){
		type = CloseBrace;
		priority = -1;
	}
	//all else is INVALID
	else{
		priority = -1;
		type = INVALID;
	}

}

int Token::value() const
{
	if(type == Integer){
		return stoi(token);
	}
	else if(type == Identifier)
		return -1;
	else
		return -2;
}

void Token::display() const
{
	string typeName;
	switch(type){
		case 0:
			typeName = "Identifier";
			break;
		case 1:
			typeName = "Integer";
			break;
		case 2:
			typeName = "Operators";
			break;
		case 3:
			typeName = "EqualSign";
			break;
		case 4:
			typeName = "OpenBrace";
			break;
		case 5:
			typeName = "CloseBrace";
			break;
		case 6:
			typeName = "INVALID";
			break;
		default:
			typeName = "nothing";
	}
	cout << "type = " << typeName << endl;
	cout << "token = " << token << " (value is " << value() << ")" << endl;
	cout << "priority = " << priority << endl;

}

Token_type Token::get_type() const
{
	return type;
}

string Token::get_token() const
{
	return token;
}

int Token::get_priority() const
{
	return priority;
}



