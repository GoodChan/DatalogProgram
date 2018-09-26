#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include "Parameter.h"
using namespace std;

class Predicate
{
public:
	Predicate() {
	}
	~Predicate() {

	}

	string ID;
	vector<Parameter> parameterVector;
};

#endif
