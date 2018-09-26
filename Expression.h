#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<iostream>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include"Token.h" 
using namespace std;

class Expression {
public:
	Expression();
	~Expression();

	string getExpression(vector<Token>& tokenVector, unsigned int& tokenIndex);
	void firstParam(vector<Token>& tokenVector, unsigned int& tokenIndex, stringstream& ss);	
	void secondParam(vector<Token>& tokenVector, unsigned int& tokenIndex, stringstream& ss);
	bool match(vector<Token> tokenVector, unsigned int tokenIndex, string matchString);

	stringstream ss;
};

#endif
