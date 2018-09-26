#ifndef RELATION_H
#define RELATION_H

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"Tuple.h"
#include"Header.h"
#include"Parameter.h"
using namespace std;

class Relation {
 public:
  Relation() {
  }
  Relation(Header header, string name) {
	 this->header = header;
	 this->name = name;
  }
  string toString(vector<Parameter> original) {
	 stringstream ss;
	 ss << name << "(";
	 for(unsigned int i = 0; i < original.size(); ++i) {
		if((original.size() - 1) == i) {
		  ss << original[i].data;
		  break;
		}
		else {
		  ss << original[i].data << ",";
		}
	 }
	 ss << ")? ";
	 if (tupleSet.size() > 0) {
		ss << "Yes(" << tupleSet.size() << ")" << endl;
		for (Tuple t: tupleSet) {
		    ss << t.toString(header);
		}
	 }
	 else {
		ss << "No" << endl;
	 }
	 return ss.str();
  }

  void addTuple(Tuple toAdd) {
	 tupleSet.insert(toAdd);
  }
  
 string name;
  std::set<Tuple> tupleSet;
  Header header;
 private:
  
};

#endif
