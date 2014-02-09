#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <iostream>

using namespace std;
// extended by varchar, int
class Attribute {
	string type;
	string value;

public:
/*********************************************************************************
	constructor
*********************************************************************************/


	Attribute(string type, string value)
		:type(type), value(value)
	{	}


/*********************************************************************************
	non-modifying functions / accessor methods
*********************************************************************************/


	string getType() { return type; }

	string getValue() { return value; }


/*********************************************************************************
	modifying functions
*********************************************************************************/

	void setValue(string newValue) {
		value = newValue;
	}
};

#endif