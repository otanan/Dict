#include <stdio.h>
#include <string.h>

#include "dict.h"
//Need to fix logic of pointers or pointers of pointers
//Consider hashing?
//Organize functions
//Implement type checking with generics
//Consider implementing memcpy in values as well, instead of just keys
//Check malloc/realloc calls

static void key_to_string(void *key, char *string);
static void key_to_string(void *key, char *string) {
	int len = strlen((char *) key) + 1;
    memcpy(string, key, len);
}


int main() {
	Dict *dict = newDict();
	dict->set_key_to_string(dict, key_to_string);

	char *label = "first";
	char *label2 = "second";
	char *label3 = "third";
	char *label4 = "fourth";
	char *label5 = "fifth";
	char *label6 = "ACCESSED WRONG";


	int x = 10;
	int y = 2;
	int z = -1;
	int a = 1;
	int b = 24328472;
	dict->set(dict, label, &x);
	dict->set(dict, label2, &y);
	dict->set(dict, label3, &z);
	dict->set(dict, label4, &a);
	dict->set(dict, label5, &b);
	dict->set(dict, label6, &x);
	//
	//
	

	dict->print(dict);


	return 0;
}