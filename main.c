#include <stdio.h>
#include "dict.h"

//Need to fix logic of pointers or pointers of pointers
//Consider hashing?
//Organize functions
//Implement type checking with generics

int main() {

	char *label = "A";
	char *label2 = "B";
	char *label3 = "C";
	int x = 2;
	int y = 27;
	int z = -32;

	Dict myDict = newDict(label, &x);
	myDict.set(myDict, label2, &x);
	myDict.set(myDict, label3, &x);
	myDict.set(myDict, label, &x);

	myDict.print(myDict);
	return 0;
}