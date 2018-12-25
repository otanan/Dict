#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 1000
#endif

/******************************Constructors******************************/
Dict *newDict() {
	Dict *self = malloc(sizeof(Dict));
	//Small capacity is for testing purposes
	self->__capacity__ = 2;
	self->__length__ = 0;

	int memNeeded = self->__capacity__ * sizeof(void *);

	//Initializes possible entries
	self->__keys__ = malloc(memNeeded);
	self->__values__ = malloc(memNeeded);

	//"METHODS"
	//Interfacing
	self->setKeyComparator = __setKeyComparator__;
	self->__keyComparator__ = __keyComparator__;

	self->setKeyToString = __setKeyToString__;
	self->__keyToString__ = __keyToString__;

	self->setValueToString = __setValueToString__;
	self->__valueToString__ = __valueToString__;
	//General Functionality
	self->print = __printDict__;
	//Getters
	self->length = __getDictLength__;
	self->capacity = __getDictCapacity__;
	self->isEmpty = __isEmptyDict__;
	self->isFull = __isFullDict__;
	self->contains = __contains__;
	self->get = __get__;
	self->getKey = __getKey__;
	//Setters
	self->set = __set__;

	return self;
}

/******************************Interfacing******************************/
void __setKeyComparator__(Dict *self, bool (*__keyComparator__)(void *key1, void *key2)) { self->__keyComparator__ = __keyComparator__; }
bool __keyComparator__(void *key1, void *key2) { return key1 == key2; }

void __setKeyToString__(Dict *self, void (*__keyToString__)(void *key, char *string)) { self->__keyToString__ = __keyToString__; }
void __keyToString__(void *key, char *string) { sprintf(string, "%d", (int)key); }

void __setValueToString__(Dict *self, void (*__valueToString__)(void *value, char *string)) { self->__valueToString__ = __valueToString__; }
void __valueToString__(void *value, char *string) { sprintf(string, "%d", (int)value); }


/******************************General Functionality******************************/
void __printDict__(Dict *self) {
	if(self->isEmpty(self)) {
		printf("Empty dictionary\n");
		return;
	}

	char keyString[MAX_LINE_LENGTH], valueString[MAX_LINE_LENGTH];

	printf("[");
	for(int i = 0; i < self->length(self); i++) {
		//Uses custom implementation of toString functions
		//if implemented, otherwises defaults
		void *key = self->getKey(self, i);

		self->__keyToString__(key, keyString);
		self->__valueToString__(self->get(self, key), valueString);

		printf("(%s, %s), ", keyString, valueString);
	}

	printf("\b\b]\n");
}

void __grow__(Dict *self) {
	//Increases the capacity by 150%
	self->__capacity__ *= 1.5;

	int memNeeded = self->capacity(self) * sizeof(void *);

	self->__keys__ = realloc(self->__keys__, memNeeded);
	self->__values__ = realloc(self->__values__, memNeeded);
}

void __replace__(Dict *self, int index, void *value) { self->__values__[index] = value; }

/******************************Getters******************************/
int __getDictCapacity__(Dict *self) { return self->__capacity__; }
int __getDictLength__(Dict *self) { return self->__length__; }
bool __isEmptyDict__(Dict *self) { return self->length(self) == 0; }
bool __isFullDict__(Dict *self) { return self->length(self) == self->capacity(self); }

void *__getKey__(Dict *self, int index) {
	if(index >= self->length(self))
		return NULL;

	return self->__keys__[index];
}

int __contains__(Dict *self, void *key) {
	//If it's empty, it won't clearly won't have a matching key
	if(self->isEmpty(self))
		return -1;

	for(int i = 0; i < self->length(self); i++) {
		//Uses the implemented keyComparator to check if the keys match
		if(self->__keyComparator__(self->__keys__[i], key))
			return i;
	}

	return -1;
}

void *__get__(Dict *self, void *key) {
	int index = self->contains(self, key);

	if(index >= 0)
		return self->__values__[index];

	return NULL;
}


/******************************Setters******************************/
void __set__(Dict *self, void *key, void *value) {
	int index = self->contains(self, key);

	if(index >= 0) {
		__replace__(self, index, value);
		return;
	}

	if(self->length(self) >= self->capacity(self))
		__grow__(self);

	//Better than mallocing all at once for storage optimization
	//required, otherwise keys made on the same stack will clash
	//This copies the contents of the key rather than linking to the same pointer
	self->__keys__[self->length(self)] = malloc(sizeof(key));
	memcpy(self->__keys__[self->length(self)], key, sizeof(*key));

	self->__values__[self->length(self)] = value;	

	//Increments the size of the dictionary
	self->__length__++;
}