#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general.h"


const int POISON_INT = -123;
const char POISON_CHAR = '~';
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

char *get_word(char *string, char *endptr) {
	if (string == NULL)
		return NULL;

	int word_len = 0;
	for (int symb_index = 0; symb_index < strlen(string); ++symb_index) {
		if (isalpha(string[symb_index])) {
			++word_len;
		}
	}

	char *word = many_atempts_calloc(word_len,
							   sizeof(char),
							   MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (word == NULL) {
		return NULL;
	}
	memcpy(word, string, word_len * sizeof(char));
	if (endptr != NULL) {
		endptr = &string[word_len];
	}

	return word;
}

int index_in_string_by_char_ptr(char *string, char *symb_ptr) {
	if (string == NULL)
		return ERR_ARG1;
	if (symb_ptr == NULL) {
		return ERR_ARG2;
	}

	return symb_ptr - string;
}

int int_len(int number) {
	int len = 1;
	if (number < 0) {
		++len;
		number = -number;
	}
	while (number > 9) {
		++len;
		number = number / 10;
	}

	return len;
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
