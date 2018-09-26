#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>
#include <vector>
#include "Predicate.h"
using namespace std;

class Rule
{
public:
	Rule(Predicate head, Predicate tail) {
		this->head = head;
		this->tail.push_back(tail);
	}
	~Rule();

	void addPredicate(Predicate tail) {
		this->tail.push_back(tail);
	}

	Predicate head;
	vector<Predicate> tail;
};

#endif
