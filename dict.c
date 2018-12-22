#include <stdio.h>
#include <stdlib.h>
#include "dict.h"

/******************************General Functionality******************************/
void __printDict__(Dict *self) {
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

void __grow__(Dict *self) {
}

void __replace__(Dict *self, int index, void *value) { self->__values__[index] = value; }

/******************************Constructors******************************/
Dict *newDict(void *key, void *value) {
	Dict *self = malloc(sizeof(Dict *));

	self->__capacity__ = 5;
	self->__length__ = 0;

	//Initializes possible entries
	self->__keys__ = malloc(self->__capacity__ * sizeof(key));
	self->__values__ = malloc(self->__capacity__ * sizeof(value));

	//"METHODS"
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

	self->set(self, key, value);

	return self;
}

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
		if( self->__keys__[i] == key)
			return i;
	}

	return -1;
}

void *__get__(Dict *self, void *key) {
	int index = self->contains(self, key);

	if(	index >= 0)
		return self->__values__[index];

	return NULL;
}


/******************************Setters******************************/
void __set__(Dict *self, void *key, void *value) {
	int index = self->contains(self, key);

	if( index >= 0) {
		__replace__(self, index, value);
		return;
	}

	if(self->length(self) >= self->capacity(self))
		__grow__(self);

	self->__keys__[self->length(self)] = key;
	self->__values__[self->length(self)] = value;

	//Incremenets the size of the dictionary
	self->__length__++;
}