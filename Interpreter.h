#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include"Header.h"
#include"Database.h"
#include"Tuple.h"
#include"Relation.h"
#include"DatalogProgram.h"
#include"Predicate.h"
#include"graph.h"
#include"graphNode.h"
using namespace std;

class Interpreter {
public:
	Interpreter(vector<Predicate>& schemes, vector<Predicate>& queries, vector<Predicate>& facts, vector<Rule>& rules) {
		this->schemes = schemes;
		this->queries = queries;
		this->facts = facts;
		this->rules = rules;
	}
	void test() {
		for (unsigned int i = 0; i < schemes.size(); ++i) {
			Header HH;
			for (unsigned int j = 0; j < schemes[i].parameterVector.size(); ++j) {
				string str;
				str = schemes[i].parameterVector[j].data;
				//cout << "string? " << str << endl;
				HH.push_back(str);
			}
			Relation add(HH, schemes[i].ID);
			database[add.name] = add;
		}

		for (unsigned int i = 0; i < facts.size(); ++i) {
			Tuple tuple;
			for (unsigned int j = 0; j < facts[i].parameterVector.size(); ++j) {
				tuple.push_back(facts[i].parameterVector[j].data);
			}
			database[facts[i].ID].addTuple(tuple);
		}
		doRules1();
		doQueries();
	}

	void doRules1() {
		vector<set<unsigned int>> components;
		graph Graph;
		components = Graph.optimizeRules(rules);
		Graph.dependencyGraphToString();

		cout << "Rule Evaluation" << endl;
		for (unsigned int i = 0; i < components.size(); ++i) {
			//for (unsigned int j = 0; j < components[i].size(); ++j) {
				doRules2(components[i]);
			//}
		}
		cout << endl;
	}

	bool checkDependsOnSelf(set<unsigned int>& rulesToEvaluate) {
		bool oneIter = false;
		if (rulesToEvaluate.size() <= 1) {
			oneIter = true;
		}
		
		for (unsigned int k = 0; k < rules[*rulesToEvaluate.begin()].tail.size(); ++k) {
			 if (rules[*rulesToEvaluate.begin()].head.ID == rules[*rulesToEvaluate.begin()].tail[k].ID) {
				oneIter = false;
			 }
		  }
	  return oneIter;
  }

	void printRuleNums(set<unsigned int>& rulesToEvaluate) {
		auto iter = rulesToEvaluate.begin();

		while (iter != rulesToEvaluate.end()) {
			cout << "R" << *iter;
			++iter;
			if (iter != rulesToEvaluate.end()) {
				cout << ",";
			}
			else {
				cout << endl;
			}
		}
	}

	void doRules2(set<unsigned int>& rulesToEvaluate) {
		Relation toReturn;
		unsigned int lastCount = 0;
		bool toRepeat = true;
		bool singleIteration = false;

		cout << "SCC: ";
		printRuleNums(rulesToEvaluate);

	while (toRepeat) {
			toRepeat = false;
			singleIteration = false;

			singleIteration = checkDependsOnSelf(rulesToEvaluate);
			
			for (unsigned int i : rulesToEvaluate) {
				vector<Relation> database2;
				cout << ruleToString(rules[i]);
				for (unsigned int j = 0; j < rules[i].tail.size(); ++j) {
					database2.push_back(evaluateQuery(database[rules[i].tail[j].ID], rules[i].tail[j]));
					if (database2.size() == 2) {
						toReturn = join(database2);
						database2.clear();
						database2.push_back(toReturn);
					}
					else if (database2.size() > 2) {
						cout << "database larger than 2" << endl;
					}
					else {
						toReturn = database2[0];
					}
				}
				toReturn = project(toReturn, rules[i]);
				if ((unionize(toReturn)) && (!singleIteration)) {
					toRepeat = true;
				}
			}
			++lastCount;
		}
	cout << lastCount << " passes: ";
	printRuleNums(rulesToEvaluate);
	//cout << endl;
  }

  string ruleToString(Rule rule) {
	  stringstream ss;

	  ss << rule.head.ID << "(";
	  for (unsigned int i = 0; i < rule.head.parameterVector.size(); ++i) {
		  if (i >= (rule.head.parameterVector.size() - 1)) {
			  ss << rule.head.parameterVector[i].data;
		  }
		  else {
			  ss << rule.head.parameterVector[i].data << ",";
		  }
	  }
	  ss << ") :- ";
	  for (unsigned int i = 0; i < rule.tail.size(); ++i) {
		  ss << rule.tail[i].ID << "(";
		  for (unsigned int j = 0; j < rule.tail[i].parameterVector.size(); ++j) {
			  if (j >= (rule.tail[i].parameterVector.size() - 1)) {
				  ss << rule.tail[i].parameterVector[j].data;
			  }
			  else {
				  ss << rule.tail[i].parameterVector[j].data << ",";
			  }
		  }
		  if (i >= (rule.tail.size() - 1)) {
			  ss << ")";
		  }
		  else {
			  ss << "),";
		  }
	  }
	  ss << "." << endl;
	  return ss.str();
  }


  bool unionize(Relation toAdd) {
	  bool tupleAdded = false;
	  for (Tuple t : toAdd.tupleSet) {
		  if (database[toAdd.name].tupleSet.count(t) == 0) {
			  cout << t.toString(database[toAdd.name].header);
			  database[toAdd.name].addTuple(t);
			  tupleAdded = true;
		  }
		  else {}
	  }
	  return tupleAdded;
  }

  Relation join(vector<Relation> toComp) {
	  map<string, unsigned int> haveSeen;
	  vector<pair<unsigned int, unsigned int>> match;
	  vector<unsigned int> unique;
	  
	   for (unsigned int j = 0; j < toComp[0].header.size(); ++j) {
			haveSeen[toComp[0].header[j]] = j;
		}
		for (unsigned int i = 0; i < toComp[1].header.size(); ++i) {
			if (haveSeen.find(toComp[1].header[i]) != haveSeen.end()) {
				pair<unsigned int, unsigned int> matching;
				matching.first = haveSeen[toComp[1].header[i]];
				matching.second = i;
				match.push_back(matching);
			}
			else {
				unique.push_back(i);
			}
		}

		Header newHeader = newHeaderJoin(toComp, unique);

		Relation toReturn(newHeader, "temp");
		return joinJoin(toComp, unique, match, toReturn, haveSeen);
  }

  Relation joinJoin(vector<Relation>& toComp, vector<unsigned int>& unique, 
		vector<pair<unsigned int, unsigned int>>& match, Relation& toReturn, 
		map<string, unsigned int>& haveSeen) {
		bool matching = true;
		for (Tuple t1 : toComp[0].tupleSet) {
			for (Tuple t2 : toComp[1].tupleSet) {
				matching = true;
				if (haveSeen.size() > 0) {
					for (pair<unsigned int, unsigned int> p : match) {
						if (t1[p.first] != t2[p.second]) {
							matching = false;
						}
					}
					if (matching) {
						toReturn.addTuple(joinCreateTuple(t1, t2, unique));
					}
				}
				else {
					toReturn.addTuple(joinCreateTuple(t1, t2, unique));
				}
			}
		}
		return toReturn;
	}

  Header newHeaderJoin(vector<Relation>& toComp, vector<unsigned int> unique) {
	 Header newHeader = toComp[0].header;
		for (unsigned int i = 0; i < unique.size(); ++i) {
			newHeader.push_back(toComp[1].header[unique[i]]);
		}
		return newHeader;
  }
  
  Relation project(Relation& rulified, Rule rule) {
	  Relation toReturn;
	  vector<int> projCol;
	  map<string, unsigned int> map;
	  Header newHeader;

	  for (unsigned int i = 0; i < rulified.header.size(); ++i) {
		  map[rulified.header[i]] = i;
	  }
	  for (unsigned int i = 0; i < rule.head.parameterVector.size(); ++i) {
		  newHeader.push_back(rule.head.parameterVector[i].data);
		  projCol.push_back(map[rule.head.parameterVector[i].data]);
	  }
	  toReturn = project(database[rule.head.ID], rulified, newHeader, projCol);

	  return toReturn;
  }

  Tuple joinCreateTuple(Tuple t1, Tuple t2, vector<unsigned int> unique) {
	  Tuple tempTuple;
	  tempTuple = t1;
	  for (unsigned int u : unique) {
		  tempTuple.push_back(t2[u]);
	  }
	  return tempTuple;
  }

  Relation doQueries() {
	 Header filler;
	 string nameFiller;
	 Relation toPrint(filler, nameFiller);

	 cout << "Query Evaluation" << endl;
	 for(unsigned int i = 0; i < queries.size(); ++i) {
	   toPrint = evaluateQuery(database[(queries[i].ID)], queries[i]);
		cout << toPrint.toString(queries[i].parameterVector);
	 }
	 
	 return toPrint;
  }

  Relation evaluateQuery(Relation relation, Predicate query) {
	 map<string, vector<int>> haveSeen;
	 vector<int> toKeep;
	 Header newHeader;
	 Relation toReturn(relation.header, relation.name);
	 toReturn = relation;
	 for(unsigned int i = 0; i < query.parameterVector.size(); ++i) {
		if (query.parameterVector[i].type == "STRING") {
		  //add asignment of changed relation to toReturn
		  toReturn = select1(relation, toReturn, query.parameterVector[i].data, i);
		}
		else if (haveSeen.find(query.parameterVector[i].data) != haveSeen.end()) {
		  int col2 = 0;
		  col2 = haveSeen[query.parameterVector[i].data].back();
		  toReturn = select2(relation, toReturn, i, col2);
		}
		else {
		  haveSeen[query.parameterVector[i].data].push_back(i);
		  toKeep.push_back(i);
		  newHeader.push_back(query.parameterVector[i].data);
		}
	 }
	 toReturn = project(relation, toReturn, newHeader, toKeep);
	 rename();
	 return toReturn;
  }

  Relation select1(Relation relation, Relation altered, string value, int col) {
	 Relation toReturn(relation.header, relation.name);
	 for (Tuple t: altered.tupleSet) {
		if (t[col] == value) {
		  //if t == value then copy and keep the tuple
		  toReturn.addTuple(t);
		}
	 }
	 return toReturn;
  }

  
  Relation select2(Relation relation, Relation altered, int col, int col2) {
	 Relation toReturn(relation.header, relation.name);
	 for (Tuple t: altered.tupleSet) {
		if (t[col] == t[col2]) {
		  toReturn.addTuple(t);
		}
	 }
	 return toReturn;
  }


  Relation project(Relation relation, Relation altered, Header newHeader, vector<int> rows) {
	  Relation toReturn(newHeader, relation.name);
	 for (Tuple t: altered.tupleSet) {
		Tuple newTuple;
		for(unsigned int i = 0; i < rows.size(); ++i) { //going trough every tuple and adding the needed row
		  newTuple.push_back(t[rows[i]]);
		  // grabing the tuple at the first row specified and adding it to the new tuple
		}
	   toReturn.addTuple(newTuple);
	 }
	 return toReturn;
  }

  string rename() {
	 return "FIXME";
  }
  
  Database database;
  	vector<Predicate> schemes;
	vector<Predicate> queries;
	vector<Predicate> facts;
	vector<Rule> rules;

};

#endif
