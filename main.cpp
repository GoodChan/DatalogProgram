#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"Token.h"
#include"Scanner.h"
#include"Interpreter.h"
#include"Predicate.h"
#include"DatalogProgram.h"
using namespace std;

int main(int argc, char **argv) {
	vector<Token> tokenVector;
	stringstream ss;
	//Interpreter itemScanner;
	Scanner itemScanner(tokenVector, argv[1]);
	tokenVector = itemScanner.startFunc();
	DatalogProgram parser(tokenVector);

	try {
	  ss << parser.datalogProgramFunction();
	  //cout << "Success!" << endl;
	  //cout << ss.str();
	}
	catch (Token e) {
	  // cout << "Failure!" << endl << "  ";
	  // e.printToken();
	}

	vector<Predicate> schemes = parser.schemes;
	  vector<Predicate> queries = parser.queries;
	  vector<Predicate> facts = parser.facts;
	  vector<Rule> rules = parser.rules;

	Interpreter interpreter(schemes, queries, facts, rules);
	interpreter.test();
	return 0;
}


