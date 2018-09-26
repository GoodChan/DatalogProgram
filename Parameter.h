#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <string>
#include "Expression.h"
using namespace std;

class Parameter {
public:
	Parameter(vector<Token>& tokenVector, unsigned int& tokenIndex) {
		if (tokenVector[tokenIndex].type == "STRING" || tokenVector[tokenIndex].type == "ID") {
			this->type = tokenVector[tokenIndex].type;
			this->data = tokenVector[tokenIndex].userString;
		}
		else if (tokenVector[tokenIndex].type == "LEFT_PAREN") {
		  Expression Express;
			data = Express.getExpression(tokenVector, tokenIndex);
		}
		else {
			throw tokenVector[tokenIndex];
		}
	}

	~Parameter();

	string type;
	string data;
};

#endif
