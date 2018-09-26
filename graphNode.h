#ifndef GRAPHNODE_H
#define GRAPHNODE_H
#include<iostream>
#include<set>

using namespace std;

class graphNode
{
public:
	graphNode() {
		this->isVisited = false;
	}
	graphNode(int ID) {
		this->ID = ID;
		this->isVisited = false;
	}
	~graphNode();

	int ID;
	set<unsigned int> dependencies;
	bool isVisited;
};
#endif
