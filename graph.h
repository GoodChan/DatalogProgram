#ifndef GRAPH_H
#define GRAPH_H
#include"graphNode.h"
#include"Rule.h"
#include<iostream>
#include<vector>
#include"Predicate.h"
#include<stack>
#include<set>
#include<map>
using namespace std;

class graph
{
public:
	graph() {
		componentCount = 0;
	}
	~graph();

	vector<set<unsigned int>> optimizeRules(vector<Rule> Rules) {
		map<string, vector<unsigned int>> headMap;
		//unsigned int var = 0;

		addRulesToGraph(Rules, headMap);
		reverseTheGraph();
		//var = reverseGraph.size();
		for (unsigned int i = 0; i < Graph.size();  ++i) {
			if (!reverseGraph[i].isVisited) {
				postOrderNumbering(i);
			}
		}
		SCC();
		if (components.size() == 0) {
			noSCC(Rules, components);
		}
		return components;
	}

	void noSCC(vector<Rule>& Rules, vector<set<unsigned int>>& components) {
		for (unsigned int i = (Rules.size()); i > 0; --i) {
			set<unsigned int> temp;
			temp.insert(i - 1);
			components.push_back(temp);
		}
	}

	void addRulesToGraph(vector<Rule>& Rules, map<string, vector<unsigned int>>& headMap) {
		for (unsigned int i = 0; i < Rules.size(); ++i) {
			headMap[Rules[i].head.ID].push_back(i);
		}
		for (unsigned int i = 0; i < Rules.size(); ++i) {
			Graph[i];
			for (unsigned int j = 0; j < Rules[i].tail.size(); ++j) {
				if (headMap.find(Rules[i].tail[j].ID) != headMap.end()) {
					for (unsigned int k = 0; k < headMap[Rules[i].tail[j].ID].size(); ++k) {
						// for every rule associated with a matching head/tail predicate's name, add it to the Graph's dependencies
						Graph[i].dependencies.insert(headMap[Rules[i].tail[j].ID][k]);
					}
				}
			}
		}
	}

	void reverseTheGraph() {
		for (unsigned int i = 0; i < Graph.size(); ++i) {
			for (unsigned int n : Graph[i].dependencies) {
				reverseGraph[n].ID = n;
				reverseGraph[n].dependencies.insert(i);
			}
			if (Graph[i].dependencies.size() == 0) {
				reverseGraph[i];
			}
		}
	}

	void postOrderNumbering(unsigned int current) {
		for (unsigned int next : reverseGraph[current].dependencies) {
		  if ((reverseGraph[next].isVisited) && (current != next)) {
				reverseGraph[current].isVisited = true;
				break;
			}
			else {
				reverseGraph[next].isVisited = true;
				if (next != current) {
					postOrderNumbering(next);
				}
			}
		}
		if (reverseGraph[current].dependencies.size() == 0) {
			reverseGraph[current].isVisited = true;
		}
		postOrderNums.push(current);
	}

	void SCC() {
		unsigned int postOrderOrigSize = postOrderNums.size();
		for (unsigned int i = 0; i < postOrderOrigSize; ++i) {
			unsigned int stackNum = postOrderNums.top();
			postOrderNums.pop();
			if (Graph[stackNum].isVisited) {
			}
			else {
				set<unsigned int> temp;
				components.push_back(findComponent(stackNum, temp));
				++componentCount;
			}
		}
	}

	set<unsigned int> findComponent(unsigned int current, set<unsigned int>& temp) {
		if (Graph[current].dependencies.size() == 0) {
			Graph[current].isVisited = true;
		}
		for (unsigned int next : Graph[current].dependencies) {
			if (Graph[next].isVisited) {
				Graph[current].isVisited = true;
			}
			else {
				if ((next != current) && (Graph[next].isVisited != true)) {
					Graph[next].isVisited = true;
					findComponent(next, temp);
				}
				else {
					Graph[current].isVisited = true;
				}
			}
		}
		temp.insert(current);
		return temp;
	}


	void dependencyGraphToString() {
		cout << "Dependency Graph" << endl;
		if (Graph.size() != 0) {
			for (unsigned int i = 0; i < Graph.size(); ++i) {
				cout << "R" << i << ":";
				auto iter = Graph[i].dependencies.begin();
				while (iter != Graph[i].dependencies.end()) {
					cout << "R" << *iter;
					++iter;
					if (iter != Graph[i].dependencies.end()) {
						cout << ",";
					}
					else {
						//cout << endl;
					}
				}
				cout << endl;
			}
			cout << endl;
		}
		else {
			for (unsigned int i = 0; i < components.size(); ++i) {
				for (unsigned int j : components[i]) {
					cout << "R" << j << ":" << endl;
				}
			}
			cout << endl;
		}
	}

	map<unsigned int, graphNode> Graph;
	map<unsigned int, graphNode> reverseGraph;
	stack<unsigned int> postOrderNums;
	vector<set<unsigned int>> components;
	unsigned int componentCount;
};

#endif
