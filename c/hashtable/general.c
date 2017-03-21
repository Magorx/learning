#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

const int SMALL_BUFFER_LENGTH = 50;

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int randstr(int len, char **string_ptr) {
	char *new_string_ptr = (char*)
		many_attempts_calloc(len + 2,
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

int normalize_string(char **string, int to_free, int full_string_len) {
	/* Normalized string is string, that starts with letter or number, ends
	   with letter or nuber and all of it's letters are small*/

	if (string == NULL)
		return ERR_NULL_OBJ;

	char *new_string = (char*)
		many_attempts_calloc(full_string_len,
							 sizeof(char),
							 MAX_MEMORY_ALLOCATION_ATTEMPTS);
	strcpy(new_string, *string);
	if (to_free == TRUE) {
		free(*string);
	}

	while (isalpha(new_string[0]) == 0 &&
		   isdigit(new_string[0]) == 0 &&
		   strlen(new_string)) {
		delete_first_character(new_string);
	}
	while (isalpha(new_string[strlen(new_string) - 1]) == 0 &&
		   isdigit(new_string[strlen(new_string) - 1]) == 0 &&
		   strlen(new_string)) {
		delete_last_character(new_string);
	}

	string_to_lower(&new_string, TRUE, full_string_len);

	*string = new_string;

	return 0;
}

int get_word(char *string, int start_index, char **word) {
	if (string == NULL)
		return ERR_NULL_OBJ;
	if (!isalpha(string[start_index]))
		return ERR_ARG2;

	char *new_word = (char*)
		many_attempts_calloc(strlen(string) - start_index + 2,
							sizeof(char),
						    MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_word == NULL) {
		return ERR_STRING_NOT_CREATED;
	}

	int symb_index = start_index;
	for (symb_index = start_index; symb_index < strlen(string); ++symb_index) {
		if (!isspace(string[symb_index])) {
			new_word[symb_index - start_index] = string[symb_index];
		} else {
			break;
		}
	}

	*word = new_word;
	return 0;
}

int string_to_lower(char **string, int to_free, int full_string_len) {
	if (string == NULL)
		return ERR_NULL_OBJ;

	char *new_string = (char*)
		many_attempts_calloc(full_string_len,
							 sizeof(char),
							 MAX_MEMORY_ALLOCATION_ATTEMPTS);
	strcpy(new_string, *string);
	if (to_free == TRUE) {
		free(*string);
	}

	int symb_index = 0;
	for (symb_index = 0; symb_index < strlen(new_string); ++symb_index) {
		new_string[symb_index] = tolower(new_string[symb_index]);
	}
	*string = new_string;

	return 0;
}

int empty_string(char *string) {
	if (string == NULL)
		return ERR_NULL_OBJ;

	int len = strlen(string);
	for (int symb_index = 0; symb_index < len; ++symb_index) {
		string[symb_index] = '\0';
	}

	return 0;
}

int delete_character(char *string, int pos) {
	if (string == NULL)
		return ERR_NULL_OBJ;
	int len = strlen(string);
	if (pos < 0 || pos >= len)
		return ERR_ARG2;

	for (int symb_index = pos; symb_index < strlen(string); ++symb_index) {
		string[symb_index] = string[symb_index + 1];
	}
	string[len - 1] = '\0';

	return 0;
}


int delete_first_character(char *string) {
	delete_character(string, 0);

	return 0;
}

int delete_last_character(char *string) {
	delete_character(string, strlen(string) - 1);

	return 0;
}

void *many_attempts_calloc(int elem_count, int elem_size, int attempt_count) {
	void *new_memory_ptr = calloc(elem_count, elem_size);
	int calloc_attempt_count = 0;
	while (new_memory_ptr == NULL && calloc_attempt_count < attempt_count) {
		new_memory_ptr = calloc(elem_count, elem_size);
		++calloc_attempt_count;
	}
	return new_memory_ptr;
}
