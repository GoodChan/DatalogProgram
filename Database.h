#ifndef DATABASE_H
#define DATABASE_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include "Relation.h"

class Database : public std::map<std::string, Relation> { };

#endif
