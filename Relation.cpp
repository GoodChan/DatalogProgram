#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"Relation.h"
#include"Tuple.h"
#include"Header.h"


/* Relation::Relation(Header header, string name) {
	 this->header = header;
	 this->name = name;
  }
  string Relation::toString() {
	 stringstream ss;
	 ss << name << "(";
	 for(unsigned int i; i < (header.size() - 1); ++i) {
		ss << header[i] << "," << endl;
	 }
	 ss << header.at((header.size() - 1)) << ")? " << endl;
	 ss << "Yes(" << tupleSet.size() << ")" << endl;
	 
	 for (Tuple t: tupleSet) {
		 for(unsigned int i; i < (t.size()-1); ++i) {
		  ss << header[i] << "=\'" << t[i] << "\', ";
		}
	 ss << header[(t.size() - 1)] << "=\'" << t[(t.size() - 1)]<< "\'" << endl;
	 }
	 return ss.str();
  }
*/

