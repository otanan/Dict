/*
*Filename: 		main.c
*Author: 		Jonathan Delgado
*Description: 	Source of entry for testing the dictionary
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dict.h"

static void key_to_string(void *key, char *string);
static void key_to_string(void *key, char *string) {
	int len = strlen((char *) key) + 1;
    memcpy(string, key, len);
}
static bool key_comparator(void *key1, void *key2) {
	return !strcmp((char *)key1, (char *)key2);
}

void hello_world(void);
void hello_world() {
	printf("Hello world!\n");
}

struct func_holder {
	void (*function)();
};

int main() {
	Dict *dict = newDict();
	dict->set_key_to_string(dict, key_to_string);
	dict->set_key_comparator(dict, key_comparator);

	char *label = "Helloworldfunc";
	dict->set(dict, label, hello_world);

	dict->print(dict);

	struct func_holder func_holder = {dict->get(dict, label)};

	func_holder.function();

	return 0;
}