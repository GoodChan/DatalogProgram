#ifndef TOKEN_H
#define TOKEN_H

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Token {

public:
	Token(string type, string userString, int lineNum);
	void printToken();
	
	string type;
	string userString;
	int lineNum;
};

#endif
