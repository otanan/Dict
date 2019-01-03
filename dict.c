/*
*Filename: 		dict.c
*Author: 		Jonathan Delgado
*Description: 	Dictionary program implementation for having basic
*				dictionary functionality in C
*/

/******************************Include******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
/******************************Define******************************/
#ifndef MAX_LINE_LENGTH
#define MAX_LINE_LENGTH 1000
#endif
//KEY_SIZE for copying keys over
//since determining the size of a void pointer is non-trivial
#define KEY_SIZE 64

/******************************PROTOTYPES******************************/

/******************************Interfacing******************************/

/*
*Function: set_key_operator
*-----------------------------
*Sets the key_comparator in the dictionary, in case a custom one is written.
*Analogous to interfaces in Java
*
*self:				the dictionary struct
*key_comparator: 	function pointer containing overridden functionality
*
*returns: 			void
*/
static void set_key_comparator(
	Dict *self,
	bool (*key_comparator)(void *key1, void *key2)
);


/*
*Function: key_comparator
*-----------------------------
*New key_comparator functionality the dictionary uses to do key checking
*
*key1: 		the first key for comparison
*key2: 		the second key for comparison
*
*returns: 	returns a boolean representing whether the keys are equal
*/
static bool key_comparator(void *key1, void *key2);

static void set_key_to_string(
	Dict *self,
	void (*key_to_string)(void *key, char *string)
);


/*
*Function: key_to_string
*-----------------------------
*New functionality for converting keys to strings for printing
*
*key: 		the key to be associated
*string: 	a pointer to the location where the string is to be stored
*
*returns: 	void
*/
static void key_to_string(void *key, char *string);

static void set_value_to_string(
	Dict *self,
	void (*value_to_string)(void *value, char *string)
);
static void value_to_string(void *value, char *string);
/****************************General Functionality****************************/
static void print_dict(Dict *self);


/*
*Function: grow
*-----------------------------
*Helper function that is called when set detects that the dictitonary
*is a maximum capacity. Serves to increase the size of the dictionary
*
*self: 		the dictionary to be increased in size
*
*returns: 	void
*/
static void grow(Dict *self);
static void replace_value(Dict *self, int index, void *value);
/******************************Getters******************************/
static int capacity(Dict *self);
static int length(Dict *self);
static bool is_empty_dict(Dict *self);
static bool is_full_dict(Dict *self);

/*
*Function: contains
*-----------------------------
*Searches for the location of a particular key in the dictionary
*
*self: 	the dictionary to be searched in
*key: 	the key to be searched for
*
*returns: 	index (nonnegative number) of the entry with the same key
*			returns -1 if the key is not found in the dictionary 
*/
static int contains(Dict *self, void *key);


/*
*Function: get
*-----------------------------
*Gets the value corresponding to the particular key in the dictionary
*
*self: 	the dictionary to be searched in
*key: 	the key to be matched
*
*returns: 	a void pointer pointing to the value
*			returns NULL if the key is not in the dictionary
*/
static void *get(Dict *self, void *key);
static void *get_key_by_index(Dict *self, int index);


/******************************Setters******************************/
static void set(Dict *self, void *key, void *value);

/******************************END PROTOTYPES******************************/



/******************************Constructors******************************/
Dict *newDict() {
	Dict *self = malloc(sizeof(Dict));
	//Small capacity is for testing purposes
	self->__capacity__ = 2;
	self->__length__ = 0;

	int mem_needed = self->__capacity__ * sizeof(void *);

	//Initializes possible entries
	self->__keys__ = malloc(mem_needed);
	self->__values__ = malloc(mem_needed);

	//"METHODS"
	//Interfacing
	self->set_key_comparator 	= set_key_comparator;
	self->__key_comparator__ 	= key_comparator;

	self->set_key_to_string 	= set_key_to_string;
	self->__key_to_string__ 	= key_to_string;

	self->set_value_to_string 	= set_value_to_string;
	self->__value_to_string__ 	= value_to_string;
	//General Functionality
	self->print 				= print_dict;
	//Getters
	self->length 				= length;
	self->capacity 				= capacity;
	self->is_empty 				= is_empty_dict;
	self->is_full 				= is_full_dict;
	self->contains 				= contains;
	self->get 					= get;
	self->get_key_by_index 		= get_key_by_index;
	//Setters
	self->set 					= set;

	return self;
}

/******************************Interfacing******************************/
static void set_key_comparator(Dict *self, bool (*key_comparator)(void *key1, void *key2)) { self->__key_comparator__ = key_comparator; }
static bool key_comparator(void *key1, void *key2) { return key1 == key2; }

static void set_key_to_string(Dict *self, void (*key_to_string)(void *key, char *string)) { self->__key_to_string__ = key_to_string; }
static void key_to_string(void *key, char *string) { sprintf(string, "%p", (int *)key); }

static void set_value_to_string(Dict *self, void (*value_to_string)(void *value, char *string)) { self->__value_to_string__ = value_to_string; }
static void value_to_string(void *value, char *string) { sprintf(string, "%p", (int *)value); }


/****************************General Functionality****************************/
static void print_dict(Dict *self) {
	if(self->is_empty(self)) {
		printf("Empty dictionary\n");
		return;
	}

	char key_string[MAX_LINE_LENGTH], value_string[MAX_LINE_LENGTH];

	printf("[");
	for(int i = 0; i < self->length(self); i++) {
		//Uses custom implementation of toString functions
		//if implemented, otherwises defaults
		void *key = self->get_key_by_index(self, i);

		self->__key_to_string__(key, key_string);
		self->__value_to_string__(self->get(self, key), value_string);

		printf("(%s, %s), ", key_string, value_string);
	}

	printf("\b\b]\n");
}

static void grow(Dict *self) {
	//Increases the capacity by 150%
	self->__capacity__ *= 1.5;

	int mem_needed = self->capacity(self) * sizeof(void *);

	self->__keys__ = realloc(self->__keys__, mem_needed);
	self->__values__ = realloc(self->__values__, mem_needed);
}

static void replace_value(Dict *self, int index, void *value) { self->__values__[index] = value; }

/******************************Getters******************************/
static int capacity(Dict *self) { return self->__capacity__; }
static int length(Dict *self) { return self->__length__; }
static bool is_empty_dict(Dict *self) { return self->length(self) == 0; }
static bool is_full_dict(Dict *self) { return self->length(self) == self->capacity(self); }

static void *get_key_by_index(Dict *self, int index) {
	if(index < 0 || index >= self->length(self)) {
		printf("Attempting to access an entry that is out of bounds.\n");
		return NULL;
	}

	return self->__keys__[index];
}

static int contains(Dict *self, void *key) {
	//If it's empty, it won't clearly won't have a matching key
	if(self->is_empty(self))
		return -1;

	for(int i = 0; i < self->length(self); i++) {
		//Uses the implemented key_comparator to check if the keys match
		if(self->__key_comparator__(self->get_key_by_index(self, i), key))
			return i;
	}

	return -1;
}

static void *get(Dict *self, void *key) {
	int index = self->contains(self, key);

	if(index >= 0)
		return self->__values__[index];

	return NULL;
}


/******************************Setters******************************/
static void set(Dict *self, void *key, void *value) {
	int index = self->contains(self, key);

	if(index >= 0) {
		replace_value(self, index, value);
		return;
	}

	if(self->length(self) >= self->capacity(self))
		grow(self);

	//Better than mallocing all at once for storage optimization
	//required, otherwise keys made on the same stack will clash
	//This copies the contents of the key rather than linking to the same pointer
	//Uses the macro defining the size of the key, notes at macro
	self->__keys__[self->length(self)] = malloc(KEY_SIZE);
	memcpy(self->__keys__[self->length(self)], key, KEY_SIZE);

	self->__values__[self->length(self)] = value;	

	//Increments the size of the dictionary
	self->__length__++;
}