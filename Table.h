#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <typeinfo>
#include "MyTuple.h"

using namespace std;


class Table {
	string tableName;
	vector<string> data;
	vector<string> types;
	vector<string> columnTitles;

	Table(string tableName, vector<string> types, vector<string> columnTitles) 
		:tableName(tableName), types(types), columnTitles(columnTitles)
	{
	}
};
