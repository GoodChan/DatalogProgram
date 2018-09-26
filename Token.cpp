#include"Token.h"

Token::Token(string type, string userString, int lineNum) {
	this->type = type;
	this->userString = userString;
	this->lineNum = lineNum;
}

void Token::printToken() {

	 cout << "(" << type << ",\"" << userString << "\"," << lineNum << ")" << endl;

}
