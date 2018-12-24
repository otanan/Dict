#include <stdio.h>
#include "dict.h"
//Need to fix logic of pointers or pointers of pointers
//Consider hashing?
//Organize functions
//Implement type checking with generics
//Consider implementing memcpy in values as well, instead of just keys


void printDict(Dict *self) {
	if(self->isEmpty(self)) {
		printf("Empty dictionary\n");
		return;
	}

	printf("[");

	for(int i = 0; i < self->length(self); i++) {
		void *key = self->getKey(self, i);
		//Temporary, already assuming that the keys are strings
		//and the values are integers
		printf("(%s, %d), ", key, *(int *)self->get(self, key));
	}

	printf("\b\b]\n");
}

int main() {

	Dict *dict = newDict();
	char *label = "first";
	char *label2 = "second";
	char *label3 = "third";
	char *label4 = "fourth";
	char *label5 = "fifth";
	
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
	dict->print(dict);


	return 0;
}