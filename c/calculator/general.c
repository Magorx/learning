#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "general.h"

const int POISON_INT = -123;
const int TRUE = 1;
const int FALSE = 0;
const int MAX_MEMORY_ALLOCATION_ATTEMPTS = 5;
const int MAX_RANDOM_STRING_LENGTH = 100;

const int ORD_a = (int) 'a';
const int ORD_z = (int) 'z';
const int ORD_A = (int) 'A';
const int ORD_Z = (int) 'Z';
const int ORD_0 = (int) '0';
const int ORD_9 = (int) '9';

const int TEST_ITER_COUNT = 100;

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int randstr(int len, char **string_ptr) {
	char *new_string_ptr = (char*)many_atempts_calloc(len + 2,
										 sizeof(char),
										 MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_string_ptr == NULL) {
		ERR_RETURN(ERR_STRING_NOT_CREATED);
	}

	int random_int = 0;
	char symb = ' ';
	int symb_index = 0;
	for (symb_index = 0; symb_index < len; ++symb_index) {
		random_int = randint(1, 3);
		switch (random_int) {
			case 1:
				symb = (char)randint(ORD_a, ORD_z);
				break;
			case 2: 
				symb = (char)randint(ORD_A, ORD_Z);
				break;
			case 3: 
				symb = (char)randint(ORD_0, ORD_9);
				break;
			default:
				symb = '~';
		}
		new_string_ptr[symb_index] = symb;
	}
	*string_ptr = new_string_ptr;
	return 0;
}

void *many_atempts_calloc(int elem_count, int elem_size, int attempt_count) {
	void *new_memory_ptr = calloc(elem_count, elem_size);
	int calloc_attempt_count = 0;
	while (new_memory_ptr == NULL && calloc_attempt_count < attempt_count) {
		new_memory_ptr = calloc(elem_count, elem_size);
		++calloc_attempt_count;
	}
	return new_memory_ptr;
}
