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

void Expression::toPostfix(){ 
	if (!stack1.empty()){
		for (int i = 0; i < stack1.size(); i++){
			stack1.pop();
		}
	}
	postfix.clear();
	for (int i = 0; i < tokenized.size(); i++){ //For each token in tokenized

		//Check to see if it is a number or letter
		if (tokenized.at(i).get_type() == Identifier || tokenized.at(i).get_type() == Integer){
			postfix.push_back(tokenized.at(i).get_token());
		}
		//Check to see if it's an openbrace
		else if (tokenized.at(i).get_type() == OpenBrace){
			stack1.push(tokenized.at(i));
		}
		//Check to see if it is a closebrace
		else if (tokenized.at(i).get_type() == CloseBrace){
			while (stack1.top().get_type() != OpenBrace){
				postfix.push_back(stack1.top());
				stack1.pop();
			}
			stack1.pop(); //Gets rid of the openbrace
		}
		else{ //Operator case
			while (!stack1.empty() && stack1.top().get_priority() >= tokenized.at(i).get_priority()){
				postfix.push_back(stack1.top());
				stack1.pop();
			}
			stack1.push(tokenized.at(i).get_token());
		}
	}
	while (!stack1.empty()){
		postfix.push_back(stack1.top());
		stack1.pop();
	}

}

void Expression::toPrefix(){ //This method is wrong
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

void Expression::evaluate(){
	//Clearing the stack
	if (!stack1.empty()){
		for (int i = 0; i < stack1.size(); i++){
			stack1.pop();
		}
	}
	//What do we do if it is a perentheses?
	//Need to read through each of the tokens
	for (int i = 0; i < postfix.size(); i++){
		if (postfix.at(i).get_type() == Identifier || postfix.at(i).get_type() == Integer){
			//If Token is an int or identifier, need to push onto stack
			stack1.push(postfix.at(i).get_token());
		}
		else if (postfix.at(i).get_type() == Operators){
			/* 
			1. Need to pop the top two off of the stack
			2. Need to apply the operation using an if statement?
			 */
			int a;
			int b;
			int tmp;
			string tmp2;
			a = stoi(stack1.top().get_token()); 
			stack1.pop();
			b = stoi(stack1.top().get_token());
			stack1.pop();
			if (postfix.at(i).get_token() == "+"){
				tmp = b + a;
			}
			else if (postfix.at(i).get_token() == "-"){
				tmp = b - a;
			}
			else if (postfix.at(i).get_token() == "*"){
				tmp = b * a;
			}
			else { //Division case
				tmp = b / a;
			}
			tmp2 = to_string(tmp); //Can't be an int, has to be a string
			stack1.push(tmp2);
		}
	}
	//Not sure what I need to do here. We should have values left of the stack that we need to evaluate.
	cout << stack1.top().get_token() << endl;
}

 void Expression::fullyParenth(){
	 parenthesized.clear();
	 if (!stack1.empty()){
		 for (int i = 0; i < stack1.size(); i++){
			 stack1.pop();
		 }
	 }
	/* 
	1. Push operands to stack
	2. Once we find an operator, pop 2 off of the stack and add them to the vector
	3. Add parentheses around the expression
	4. repeat until finished
	5. return stack.top()
	6. stack.pop()
	 */
	for (int i = 0; i < postfix.size(); i++){
		parenthesized.clear();
		if (postfix.at(i).get_type() == Identifier || postfix.at(i).get_type() == Integer){
			stack1.push(postfix.at(i).get_token()); //Pusing integers and Identifiers
		}
		else if (postfix.at(i).get_type() == Operators){ 
			string a;
			string b;
			string open = "(";
			string close = ")";
			string tmp;
			if (tmp.empty()){
				a = stack1.top().get_token();
				stack1.pop();
				b = stack1.top().get_token();
				stack1.pop();
				parenthesized.push_back(a); //Inserting int
				parenthesized.insert(parenthesized.begin(), postfix.at(i).get_token()); //Inserting operator
				parenthesized.insert(parenthesized.begin(),b); //Inserting int
			}
			else{
				a = stack1.top().get_token();
				stack1.pop();
				parenthesized.insert(parenthesized.begin(),postfix.at(i).get_token()); //Inserting operator first
				parenthesized.insert(parenthesized.begin(),a); //inserting operand
			}
			//Insert parentheses
			parenthesized.push_back(close);
			parenthesized.insert(parenthesized.begin(),open);
			for (int i = 0; i < parenthesized.size(); i++){
				tmp+= parenthesized.at(i).get_token();
			}
			stack1.push(tmp);
		}
	}
	cout << stack1.top().get_token() << endl;
}

Exp_type Expression::getType(){
	return type;
}



