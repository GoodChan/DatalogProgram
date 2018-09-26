#include "DatalogProgram.h"
#include <vector>
#include <set>
using namespace std;


DatalogProgram::DatalogProgram(vector<Token> tokenVector)
{
  indexCounter = 0;
  this->tokenVector = tokenVector;
}


DatalogProgram::~DatalogProgram()
{
}

string DatalogProgram::match(string matchString) {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == matchString) {
			return tokenVector[indexCounter].userString;
		}
		else {
			throw tokenVector[indexCounter];
		}
	}
	return "hit end of Datalogprogram::match";
}

string DatalogProgram::datalogProgramFunction() {
  stringstream ss;
  match("SCHEMES");
	++indexCounter;
	match("COLON");
	++indexCounter;
	scheme();
	schemeList();

	match("FACTS");
	++indexCounter;
	match("COLON");
	++indexCounter;
	factList();

	match("RULES");
	++indexCounter;
	match("COLON");
	++indexCounter;
	ruleList();

	match("QUERIES");
	++indexCounter;
	match("COLON");
	++indexCounter;
	query();
	queryList();
	if (indexCounter < tokenVector.size()) {
		throw tokenVector[indexCounter];
	}
	ss << schemesToString();
	ss << factsToString();
	ss << rulesToString();
	ss << queriesToString();
	ss << domainToString();
	return ss.str();
}

void DatalogProgram::scheme() {
	headPredicate(schemes);
}

void DatalogProgram::headPredicate(vector<Predicate>& toAdd) {
	Predicate temp;

	match("ID");
	temp.ID = tokenVector[indexCounter].userString;
	++indexCounter;
	match("LEFT_PAREN");
	++indexCounter;
	match("ID");
	Parameter tempParameter(tokenVector, indexCounter);
	temp.parameterVector.push_back(tempParameter);
	++indexCounter;
	idList(temp);
	match("RIGHT_PAREN");
	++indexCounter;
	toAdd.push_back(temp);
	return;
}

void DatalogProgram::idList(Predicate& toAdd) {

	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "COMMA") {
			match("COMMA");
			++indexCounter;
			match("ID");
			Parameter tempParameter2(tokenVector, indexCounter);
			toAdd.parameterVector.push_back(tempParameter2);
			++indexCounter;
			idList(toAdd);
		}
		else {
			return;
		}
	}
}

void DatalogProgram::schemeList() {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "ID") {
			scheme();
			schemeList();
		}
		else {
			return;
		}
	}
}

void DatalogProgram::factList() {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "ID") {
			fact();
			factList();
		}
		else {
			return;
		}
	}
}

void DatalogProgram::fact() {
	Predicate tempPredicate;

	tempPredicate.ID = match("ID");
	++indexCounter;
	match("LEFT_PAREN");
	++indexCounter;
	Parameter tempParameter(tokenVector, indexCounter);
	if (tempParameter.type == "STRING") {
		domain.insert(tempParameter.data);
	}
	tempPredicate.parameterVector.push_back(tempParameter);
	++indexCounter;
	stringList(tempPredicate);

	match("RIGHT_PAREN");
	++indexCounter;
	match("PERIOD");
	++indexCounter;
	facts.push_back(tempPredicate);
}

void DatalogProgram::stringList(Predicate& toAdd) {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "COMMA") {
			match("COMMA");
			++indexCounter;
			match("STRING");
			Parameter tempParameter(tokenVector, indexCounter);
			if (tempParameter.type == "STRING") {
				domain.insert(tempParameter.data);
			}
			toAdd.parameterVector.push_back(tempParameter);
			++indexCounter;
			stringList(toAdd);			
		}
		else {
			return;
		}
	}
}


void DatalogProgram::ruleList() {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "ID") {
			rule();
			ruleList();
		}
		else {
			return;
		}
	}
}

void DatalogProgram::rule() {
	vector<Predicate> tempVector;
	headPredicate(tempVector);
	
	match("COLON_DASH");
	++indexCounter;
	Rule temp(tempVector.front(), predicate());
	predicateList(temp.tail);

	match("PERIOD");
	++indexCounter;
	rules.push_back(temp);
}

Predicate DatalogProgram::predicate() {
	Predicate temp;

	temp.ID = tokenVector[indexCounter].userString;
	++indexCounter;
	match("LEFT_PAREN");
	++indexCounter;
	/*unsigned int temp1 = indexCounter + 1;
		  unsigned int temp2 = indexCounter + 2;
		  cout << "from datalog program" << tokenVector[indexCounter].type << " " << tokenVector[temp1].type << " " << tokenVector[temp2].type << endl;	 */
	temp.parameterVector.push_back(parameter());
	parameterList(temp);

	match("RIGHT_PAREN");
	++indexCounter;
	return temp;
}

Parameter DatalogProgram::parameter() {
	if (tokenVector.size() > indexCounter) {
		Parameter toReturn(tokenVector, indexCounter);
		++indexCounter;
		return toReturn;
	}
	else {
		throw tokenVector[indexCounter];
	}
}

/*void DatalogProgram::expression() {
	cout << "expression()" << endl;
	match("LEFT_PAREN");
	++indexCounter;
	parameter();
	operator1();
	parameter();
	match("RIGHT_PAREN");
	++indexCounter;
}

void DatalogProgram::operator1() {
	cout << "operator1()" << endl;
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "ADD") {
			++indexCounter;
		}
		else if (tokenVector[indexCounter].type == "MULTIPLY") {
			++indexCounter;
		}
		else {
			throw tokenVector[indexCounter];
		}
	}
}*/

void DatalogProgram::parameterList(Predicate& toAdd) {	
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "COMMA") {
			match("COMMA");
			++indexCounter;
			toAdd.parameterVector.push_back(parameter());
			parameterList(toAdd);
		}
		else {
			return;
		}
	}
}

void DatalogProgram::predicateList(vector<Predicate>& toAdd) {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "COMMA") {
			match("COMMA");
			++indexCounter;
			toAdd.push_back(predicate());
			predicateList(toAdd);
		}
		else {
			return;
		}
	}
}

void DatalogProgram::query() {
	queries.push_back(predicate());
	match("Q_MARK");
	++indexCounter;
}

void DatalogProgram::queryList() {
	if (tokenVector.size() > indexCounter) {
		if (tokenVector[indexCounter].type == "ID") {
			query();
			queryList();
		}
		else {
			return;
		}
	}
}

string DatalogProgram::schemesToString() {
  stringstream ss;
  ss << "Schemes(" << schemes.size() << "):" << endl;
  
	for (unsigned int i = 0; i < schemes.size(); ++i) {
		ss << "  " << schemes[i].ID << "(";
		for (unsigned int j = 0; j < schemes[i].parameterVector.size(); ++j) {
			if (schemes[i].parameterVector.size() == (j + 1)) {
				ss << schemes[i].parameterVector[j].data;
			}
			else {
				ss << schemes[i].parameterVector[j].data << ",";
			}
		}
		ss << ")" << endl;
	}
	return ss.str();
}

string DatalogProgram::factsToString() {
  stringstream ss;
  ss << "Facts(" << facts.size() << "):" << endl;
  
  for (unsigned int i = 0; i < facts.size(); ++i) {
		ss << "  " << facts[i].ID << "(";
		for (unsigned int j = 0; j < facts[i].parameterVector.size(); ++j) {
			if ((facts[i].parameterVector.size() - 1) == j) {
				ss << facts[i].parameterVector[j].data;
			}
			else {
				ss << facts[i].parameterVector[j].data << ",";
			}
		}
		ss << ")." << endl;
	}
  return ss.str();
}

string DatalogProgram::rulesToString() {
  stringstream ss;
  ss << "Rules(" << rules.size() << "):" << endl;
  
  for (unsigned int i = 0; i < rules.size(); ++i) {
	 ss << "  " << rules[i].head.ID << "(";
	 for(unsigned int l = 0; l < rules[i].head.parameterVector.size(); ++l) {
		if((rules[i].head.parameterVector.size()- 1) == l) {
		  ss << rules[i].head.parameterVector[l].data;
		}
		else {
		  ss << rules[i].head.parameterVector[l].data << ",";
		}
	 }
	 ss << ")" << " :- ";
		for (unsigned int j = 0; j < rules[i].tail.size(); ++j) {
			ss << rules[i].tail[j].ID << "(";
			for (unsigned int k = 0; k < rules[i].tail[j].parameterVector.size(); ++k) {
				if ((rules[i].tail[j].parameterVector.size() - 1) == k) {
					if ((rules[i].tail.size() - 1) == j) {
						ss << rules[i].tail[j].parameterVector[k].data << ").";
					}
					else {
						ss << rules[i].tail[j].parameterVector[k].data << "),";
					}
				}
				else {
					ss << rules[i].tail[j].parameterVector[k].data << ",";
				}
			}
		}
		ss << endl;
	}
	return ss.str();
}

string DatalogProgram::queriesToString() {
  stringstream ss;
	ss << "Queries(" << queries.size() << "):" << endl;

	for (unsigned int i = 0; i < queries.size(); ++i) {
		ss << "  " << queries[i].ID << "(";
		for (unsigned int j = 0; j < queries[i].parameterVector.size(); ++j) {
			if ((queries[i].parameterVector.size() - 1) == j) {
				ss << queries[i].parameterVector[j].data;
			}
			else {
				ss << queries[i].parameterVector[j].data << ",";
			}
		}
		ss << ")?" << endl;
	}
	return ss.str();
}

string DatalogProgram::domainToString() {
  stringstream ss;
  
	ss << "Domain(" << domain.size() << "):" << endl;
	
	for (set<string>::iterator it = domain.begin(); it != domain.end(); it++) {
	  ss << "  " << *it << endl;
	}
	return ss.str();
}
