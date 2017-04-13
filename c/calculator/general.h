#ifndef GENERAL_H
#define GENERAL_H

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
		if (comparator(first, second) != TRUE) { \
			printf("ASSERTION FAILED\n"); \
			exit(EXIT_SUCCESS); \
		} \
	} while (0); \

#define EXPECT_CMP_EQ(first, second, comparator) \
	do { \
		if (comparator(first, second) != TRUE) { \
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
extern const int TRUE;
extern const int FALSE;
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
int32_t get_number( char *string, int start_index, double *number);
int get_word(char *string, int start_index, char **word);
int int_len(int number);
int _int_len(int number, int len_count);
void *many_atempts_calloc(int elem_count, int elem_size, int attempt_count);

#endif  // GENERAL_H
