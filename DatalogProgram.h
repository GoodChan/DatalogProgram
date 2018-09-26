#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <string>
#include <set>
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "Expression.h"


class DatalogProgram
{
public:
  DatalogProgram() {}
	DatalogProgram(vector<Token> tokenVector);
	~DatalogProgram();

	string match(string matchString);
	string datalogProgramFunction();
	void scheme();
	void headPredicate(vector<Predicate>& toAdd);
	void idList(Predicate& toAdd);
	void schemeList();
	void factList();
	void fact();
	void stringList(Predicate& toAdd);
	void ruleList();
	void rule();
	Predicate predicate();
	Parameter parameter();
	/*void expression();
	void operator1();*/
	void predicateList(vector<Predicate>& toAdd);
	void parameterList(Predicate& toAdd);
	void query();
	void queryList();
	string schemesToString();
	string factsToString();
	string rulesToString();
	string queriesToString();
	string domainToString();

	unsigned int indexCounter;
	set<string> domain;
	vector<Token> tokenVector;
	vector<Predicate> schemes;
	vector<Predicate> queries;
	vector<Predicate> facts;
	vector<Rule> rules;
};

#endif
