#ifndef SCAN_H
#define SCAN_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include"Token.h"
using namespace std;

char blockChar = '|';
char stringChar = '\'';
char commentChar = '#';
bool debug = true;

class Scanner {
public:
	char nextChar = ' ';
	string idString = "";
	int lineNum = 1;
	int tokenNum = 0;
	string inputString = "";
	int tempLineNum = 0;
	vector<Token> tokenVector;
	ifstream input;
	ofstream output;


	Scanner(vector<Token>& tokenVector, string fileName) {
		input.open(fileName);
		if (!input.is_open()) {
			//cout << "error in input file: " << fileName.str() << endl;
		}
		else {
		}

		output.open("outFile.txt");
		if (!output.is_open()) {
			//cout << "error in input file: outFile.txt. Does it exist?" << endl;
		}
		else {
		}

		this->tokenVector = tokenVector;
	}

	void printUndef(ofstream &output, string inputString, int lineNum) {
		stringstream ss;
		/**/		ss << "" << inputString << "";
		tokenVector.push_back(Token("UNDEFINED", ss.str(), lineNum));
		//cout << "(UNDEFINED,\"" << inputString << "\"," << lineNum << ")" << endl;
	}

	bool getString(ifstream &input, ofstream &output, string &inputString, int &lineNum, int tempLineNum) {
		bool isString = true;

		while (input.peek() != stringChar) {
			if (input.eof()) {
				return false;
				break;
			}
			if (input.peek() == '\n') {
				++lineNum;
			}
			inputString += input.get();
		}
		inputString += input.get(); //removes remaining ' after finding the string;
		if (input.peek() == stringChar) {
			inputString += input.get();  //gets rid of the initial '
			if (!getString(input, output, inputString, lineNum, tempLineNum)) {
				return false;
			}
		}
		if (isString) {
			return true;
		}
		else { //if the string has no closing ' make it undefined
			return false;
		}
	}

	void stringFunc(ifstream &input, ofstream &output, string &inputString, int &lineNum, int tempLineNum) {
		stringstream ss;
		bool isString = getString(input, output, inputString, lineNum, tempLineNum);
		if (isString) {
/*took "" out of ss*/			ss << "" << inputString << "";
			tokenVector.push_back(Token("STRING", ss.str(), tempLineNum));
			//cout << "(STRING,\"" << inputString << "\"," << tempLineNum << ")" << endl;
		}
		else { //if the string has no closing ' make it undefined
			ss << "" << inputString << "";
			tokenVector.push_back(Token("UNDEFINED", ss.str(), tempLineNum));
			//cout << "(UNDEFINED,\"" << inputString << "\"," << tempLineNum << ")" << endl;
		}
	}

	bool isCommentBlock(ifstream &input, char nextchar) { //need to add const?
		bool isComment = false;
		if (input.peek() == blockChar) {
			isComment = true;
		}
		return isComment;
	}

	string notCommentBlock(ifstream &input) {
		string commentString = "#";
		while ((input.peek() != '\n') && (!input.eof())) {
			commentString += input.get();
		}
		return commentString;
	}

	bool commentBlock(ifstream &input, string &inputString, int &lineNum) {
		inputString = "#";
		bool closed = true;
		while (!input.eof()) {
			if (input.peek() == '\n') {
				++lineNum;
			}
			if (input.peek() == blockChar) {
				inputString += input.get();
				if (input.peek() == commentChar) {
					break;
				}
			}
			else {
				if (!input.eof()) { inputString += input.get(); }
			}
		}
		if (input.eof()) {
			closed = false;
			return closed;
		}
		if (!input.eof()) {
			inputString += input.get(); //pop off remaining #
		}
		return closed;
	}

	void KeywordCheck(ifstream &input, ofstream &output, string inputString, int lineNum) {
		while (isalnum(input.peek())) {
			inputString += input.get();
		}
		if (inputString == "Schemes") {
			tokenVector.push_back(Token("SCHEMES", "Schemes", lineNum));
			return;
		}
		else if (inputString == "Facts") {
			tokenVector.push_back(Token("FACTS", "Facts", lineNum));
			//			 cout << "(FACTS,\"" << inputString << "\"," << lineNum << ")" << endl;
			return;
		}
		else if (inputString == "Rules") {
			tokenVector.push_back(Token("RULES", "Rules", lineNum));
			//cout << "(RULES,\"" << inputString << "\"," << lineNum << ")" << endl;
			return;
		}
		else if (inputString == "Queries") {
			tokenVector.push_back(Token("QUERIES", "Queries", lineNum));
			//cout << "(QUERIES,\"" << inputString << "\"," << lineNum << ")" << endl;
			return;
		}
		else {
			stringstream ID;
/**/			ID << "" << inputString << "";												//ID String changed with no "" anymore
			tokenVector.push_back(Token("ID", ID.str(), lineNum));
			// cout << "(ID,\"" << inputString << "\"," << lineNum << ")" << endl;
			return;
		}
	}

	void defaultFunc(ifstream &input, ofstream &output, char nextChar, string inputString, int &tokenNum, int lineNum) {
		if (input.eof()) {
			return;
		}
		inputString = nextChar;
		if ((!isspace(nextChar) && (nextChar != '\n'))) { //catches and ignores spaces
			++tokenNum;
			if (isalpha(nextChar)) {
				KeywordCheck(input, output, inputString, lineNum);
			}
			else {
				stringstream ss;
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("UNDEFINED", ss.str(), lineNum));
				// cout << "(UNDEFINED,\"" << inputString << "\"," << lineNum << ")" << endl;
			}
			return;;
		}
	}

	vector<Token> startFunc() {
		stringstream ss;
		/*enum TT { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,COLON, COLOND, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, ENDEFINED, EOF }*/
		while (!input.eof()) {
			nextChar = input.get();

			switch (nextChar) {

				// single char options first	
			case '\n':
				++lineNum;
				break;
			case ',':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("COMMA", ss.str(), lineNum));
				++tokenNum;
				break;
			case '.':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("PERIOD", ss.str(), lineNum));
				++tokenNum;
				break;
			case '?':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("Q_MARK", ss.str(), lineNum));
				++tokenNum;
				break;
			case '(':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("LEFT_PAREN", ss.str(), lineNum));
				++tokenNum;
				break;
			case ')':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("RIGHT_PAREN", ss.str(), lineNum));
				++tokenNum;
				break;
			case ':':
				ss.str("");
				ss << "" << nextChar << "";
				if (input.peek() == '-') {        //checks for :- which is a separate token
					input.get();
					tokenVector.push_back(Token("COLON_DASH", ":-", lineNum));
					++tokenNum;
					break;
				}
				tokenVector.push_back(Token("COLON", ss.str(), lineNum));
				++tokenNum;
				break;
			case '*':
				ss.str("");
				ss << "" << nextChar << "";
				tokenVector.push_back(Token("MULTIPLY", ss.str(), lineNum));
				++tokenNum;
				break;
			case '+':
				ss.str("");
/*took out \"*/				ss << "" << nextChar << "";
				tokenVector.push_back(Token("ADD", ss.str(), lineNum));
				++tokenNum;
				break;
			case '\'':
				tempLineNum = lineNum;  // store the first line line number
				inputString = "\'"; //adds the first ' that was found
				stringFunc(input, output, inputString, lineNum, tempLineNum);
				++tokenNum;
				break;
			case '#':
				inputString = "";
				tempLineNum = lineNum; //storing the begining line number
				if (!isCommentBlock(input, nextChar)) {
					inputString = notCommentBlock(input);
				}
				else {
					if (!commentBlock(input, inputString, lineNum)) {
						printUndef(output, inputString, tempLineNum);
						++tokenNum;
						break;
					}
				}
				ss.str("");
				ss << "" << inputString << "";
/*ADD FOR PROJ1*/ //tokenVector.push_back(Token("COMMENT", ss.str(), tempLineNum));
				++tokenNum;
				break;
				/////////////////////////////////could be misisng something
				//ID/keyword check
			default:
				defaultFunc(input, output, nextChar, inputString, tokenNum, lineNum);
				break;
			}
		}
/*ADD FOR PROJ1*/		//tokenVector.push_back(Token("EOF", "\"\"", lineNum));
		++tokenNum;
		return tokenVector;
		//input.close();
	}
};

#endif
