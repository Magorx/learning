#ifndef GENERAL_H
#define GENERAL_H

#include <stdlib.h>
#include <stdbool.h>

#define DEBUG if(DEBUG_MODE == true) \


#define ERR_RETURN(err_code) \
    do { \
        printf("ERROR [%s]:\n", #err_code); \
		printf("file [%s],\n", __FILE__); \
		printf("function [%s],\n", __FUNCTION__); \
		printf("line [%d]\n", __LINE__); \
        return err_code; \
    } while (0);

#define ASSERT_EQ(first, second) \
	do { \
		if (first != second) { \
			printf("ASSERTION FAILED\n"); \
			exit(EXIT_SUCCESS); \
		} \
	} while (0); \

#define EXPECT_EQ(first, second)\
	do { \
		if (first != second) { \
			printf("EXPECTATION ERROR\n"); \
		} \
	} while (0); \

#define ASSERT_CMP_EQ(first, second, comparator) \
	do { \
		if (comparator(first, second) != true) { \
			printf("ASSERTION FAILED\n"); \
			exit(EXIT_SUCCESS); \
		} \
	} while (0); \

#define EXPECT_CMP_EQ(first, second, comparator) \
	do { \
		if (comparator(first, second) != true) { \
			printf("EXPECTATION ERROR\n"); \
		} \
	} while (0); \

enum GENERAL_ERRORS {
	ERR_ARG1 = -10,
	ERR_ARG2,
	ERR_ARG3,
	ERR_NULL_OBJ,
	ERR_STRING_NOT_CREATED,
};

extern const int POISON_INT;
extern const char POISON_CHAR;
extern const int MAX_MEMORY_ALLOCATION_ATTEMPTS;
extern const int MAX_RANDOM_STRING_LENGT;

extern const int ORD_a;
extern const int ORD_z;
extern const int ORD_A;
extern const int ORD_Z;
extern const int ORD_0;
extern const int ORD_9;

extern const int TEST_ITER_COUNT;

int randint(int min, int max);
int randstr(int len, char **string_pointer);
char *get_word(char *string, char *endptr);
int index_in_string_by_char_ptr(char *string, char *symb_ptr);
int int_len(int number);
void *many_atempts_calloc(int elem_count, int elem_size, int attempt_count);

#endif  // GENERAL_H
