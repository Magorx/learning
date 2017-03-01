#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general.h"

const int POISON_INT = -123;
const char POISON_CHAR = '~';
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

int get_number(char *string, int start_index, int *number) {
	if (string == NULL)
		return ERR_NULL_OBJ;
	if (!isdigit(string[start_index]))
		return ERR_ARG2;

	int symb_index = start_index;
	int cur_num = 0;
	for (symb_index = start_index; symb_index < strlen(string); ++symb_index) {
		if isdigit(string[symb_index]) {
			cur_num = cur_num * 10 + ((int)string[symb_index] - ORD_0);
		} else {
			break;
		}
	}

	*number = cur_num;
	return 0;
}

int get_word(char *string, int start_index, char **word) {
	if (string == NULL)
		return ERR_NULL_OBJ;
	if (!isalpha(string[start_index]))
		return ERR_ARG2;

	char *new_word = (char*)
		many_atempts_calloc(strlen(string) - start_index + 2,
							sizeof(char),
						    MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_word == NULL) {
		return ERR_STRING_NOT_CREATED;
	}

	int symb_index = start_index;
	for (symb_index = start_index; symb_index < strlen(string); ++symb_index) {
		if (isalpha(string[symb_index])) {
			new_word[symb_index - start_index] = string[symb_index];
		} else {
			break;
		}
	}

	*word = new_word;
	return 0;
}

int int_len(int number) {
	if (number < 0) {
		return _int_len(-number, 1);
	} else {
		return _int_len(number, 0);
	}
}

int _int_len(int number, int len_count) {
	if (number >= 0 && number <= 9) {
		return len_count + 1;
	} else {
		return _int_len(number / 10, len_count + 1);
	}
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
