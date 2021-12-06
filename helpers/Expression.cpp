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
		else if (s[i] == ';'){
			continue;
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
	postfix.clear();
	for (int i = 0; i < tokenized.size(); i++){ //For each token in tokenized

		//Check to see if it is a number or letter
		if (tokenized.at(i).get_type() == Identifier || tokenized.at(i).get_type() == Integer){
			postfix.push_back(tokenized.at(i).get_token());
		}
		//Check to see if it's an openbrace
		else if (tokenized.at(i).get_type() == OpenBrace){
			stack.push(tokenized.at(i));
		}
		//Check to see if it is a closebrace
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

void Expression::toPrefix(){
	postfix.clear();
	prefix.clear();
	toPostfix();
	reverse(postfix.begin(), postfix.end());
	prefix = postfix;
}


void Expression::displayPostfix(){
	for (int i = 0; i < postfix.size(); i++){
		cout << postfix.at(i).get_token();
	}
	cout << endl;
}
void Expression::displayPrefix(){
	for (int i = 0; i < prefix.size(); i++){
		cout << prefix.at(i).get_token();
	}
	cout << endl;
}

void Expression::clearWorkingTree(){
	tokenized.clear();
	original.clear();
	postfix.clear();
}

void Expression::addToExpression(const string input){
	tokenized.clear();
	string tmp = original + input;
	cout << tmp << endl;
	set(tmp);
}

void Expression::syntaxCheck(){
	enum States {expect_operand, expect_operator, done};
	bool eq = false; //We will set this to true if we encounter an equal sign
	States state = expect_operand;
	int pcount = 0;
	valid = true; 
	int i = 0; //Make sure we don't go past the last token
	while (state != done && i < tokenized.size()){
		Token t = tokenized.at(i);
		switch (state){
			case expect_operand:
				if (t.get_type() == OpenBrace){
					pcount++;
				}
				else if (t.get_type() == Integer || t.get_type() == Identifier){
					state = expect_operator;
				}
				else{
					valid = false;
					state = done;
				}
				break;
			case expect_operator:
				if (t.get_type() == CloseBrace){
					pcount--;
					if (pcount < 0){
						valid = false;
						state = done;
					}
				}
				else if (t.get_type() == EqualSign){
					eq = true;
					state = expect_operand;
				}
				else if (t.get_type() == Operators){
					state = expect_operand;
				}
				else{
					valid = false;
					state = done;
				}
			default:
				break;
		}
	}
	if (pcount != 0){
		valid = false;
	}
	if (state == expect_operand){
		valid = false;
	}
	if (valid){
		if  (eq){
			if (tokenized.size() == 3 && tokenized.at(0).get_type() == Identifier && tokenized.at(2).get_type() == Integer){
				type = Assignment;
				//Need to use maps
				map<string,string>::iterator itr = mp.find(tokenized.at(0).get_token());
				if (itr != mp.end()){ //If we find the token in our map
					itr->second = tokenized.at(2).get_token();
				}
				else{ //If the token is not in our map
					mp.insert(pair<string,string>(tokenized.at(0).get_token(),tokenized.at(2).get_token()));
				}
			}

		}
		else{
			valid = false;
		}
	}
	else{
		type = Arithmetic;
	}
}

int Expression::evaluatePostfix(){

}



