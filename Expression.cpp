#include "Expression.h"




Expression::Expression()
{
}

Expression::~Expression()
{
}

void Expression::firstParam(vector<Token>& tokenVector, unsigned int& tokenIndex, stringstream& ss) {
  if (match(tokenVector, tokenIndex, "LEFT_PAREN")) {
	 //cout << ss.str() << "Calls itself " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
		getExpression(tokenVector, tokenIndex);
		//cout << "does it return" << endl;
		if (tokenVector[tokenIndex].type == "RIGHT_PAREN") {
			  ++tokenIndex;
		}
		//cout << ss.str() << "returns Calls itself " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
	
  }
	else if ((!match(tokenVector, tokenIndex, "STRING")) && (!match(tokenVector, tokenIndex, "ID"))) {
	  //cout << ss.str() << "Throw err1 " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
		throw tokenVector[tokenIndex];
	}
	else {
	  	ss << tokenVector[tokenIndex].userString;
		++tokenIndex;
		//cout << ss.str() << "grabs it " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
	}
}

void Expression::secondParam(vector<Token>& tokenVector, unsigned int& tokenIndex, stringstream& ss) {
if (tokenVector.size() > tokenIndex) {
		if (match(tokenVector, tokenIndex, "LEFT_PAREN")) {
			getExpression(tokenVector, tokenIndex);
			if (tokenVector[tokenIndex].type == "RIGHT_PAREN") {
			  ++tokenIndex;
			  }
			//cout << ss.str() << "Calls itself " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
	
		}
		else if ((!match(tokenVector, tokenIndex, "STRING")) && (!match(tokenVector, tokenIndex, "ID"))) {
		  //cout << ss.str() << "erroperator " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;	
		  throw tokenVector[tokenIndex];
		}
		else {
		  	ss << tokenVector[tokenIndex].userString;
			++tokenIndex;
			//cout << ss.str() << "grabs stuffCalls itself " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
	
		}
	}
}


string Expression::getExpression(vector<Token>& tokenVector, unsigned int& tokenIndex) {
	//note: send me what is inside the parenth
  //cout << "Expression" << endl;
  ss << "(";
	++tokenIndex;
	firstParam(tokenVector, tokenIndex, ss);
	if (tokenVector.size() > tokenIndex) {
		if ((tokenVector[tokenIndex].type != "ADD") && (tokenVector[tokenIndex].type != "MULTIPLY")) {
		  //cout << ss.str() << "err operator " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
		  throw tokenVector[tokenIndex];
		}
		else {
		  	ss << tokenVector[tokenIndex].userString;
			++tokenIndex;
			//cout << ss.str() << "grabs stuff " << tokenVector[tokenIndex].type << " " << tokenIndex << endl;
 
			
		}
	}
	secondParam(tokenVector, tokenIndex, ss);
	ss << ")";
	return ss.str();
}

bool Expression::match(vector<Token> tokenVector, unsigned int tokenIndex, string matchString) {
	if (tokenVector[tokenIndex].type == matchString) {
		return true;
	}
	else {
		return false;
		
	}
}
