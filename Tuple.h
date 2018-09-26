#ifndef TUPLE_H
#define TUPLE_H


#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include "Header.h"
using namespace std;

class Tuple : public vector<string> {
  public:
  string toString(Header header) {
	 stringstream ss;
	 if (this->size() > 0) {
	 ss << "  ";
	 }
	 for(unsigned int i = 0; i < this->size(); ++i) {
		if((header.size() - 1) == i) {
		  ss << header[i] << "=" << this->at(i) << "" << endl;
		  break;
		}
		else {
		  ss << header[i] << "=" << this->at(i) << ", ";
		}
	 }
	 return ss.str();
  }
};

#endif
