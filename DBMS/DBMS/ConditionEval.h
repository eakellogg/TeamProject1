/*


This header file creates shows what the evaluation method of a condition tree would look like
and how it would work. 
It ofcourse needs to be implemented in the table class because the table class knows the values of the columns 
In my example the condition tree is evaluated assuming all nodes are either operators or literals. I will write some 
pseudo code of how it would work with the table as well -Zach Brown
*/

#ifndef CONDITIONEVAL_H
#define CONDITIONEVAL_H

#include "ConditionTree.h"
#include <tuple>
#include <stdlib.h>
using namespace std;

int compareStringInts(string lv, string rv); //Returns 0 is equal, -1 if lv < rv and 1 if lv > rv


//Will return TRUE or FALSE
//Unless trees formated incorectly
string EvalConditionTree(ConditionTree* tree);

//tuple< type , value >
tuple<string, string> NodeEval(ConditionTree::Node* n);

#endif 