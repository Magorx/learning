#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "calculator.h"

const int32_t NUMBER = 1;
const int32_t ID = 2;
const int32_t SYMB = 3;
const int32_t UNUSED = 4;
const int32_t MAX_ID_LEN = 20;

#define arr_size(arr)  (sizeof arr / sizeof arr[0])

struct token *token_construct_unused() {
    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->type = UNUSED;

    return new_token;
}

struct token *token_construct_number(double number) {
    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->id = (char*)
        many_atempts_calloc(MAX_ID_LEN,
                            sizeof(char),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token->id == NULL) {
        return NULL;
    }

    new_token->number = number;
    new_token->type = NUMBER;

    return new_token;
};

struct token *token_construct_id(char *id) {
    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->id = (char*)
        many_atempts_calloc(MAX_ID_LEN,
                            sizeof(char),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token->id == NULL) {
        return NULL;
    }

    new_token->id = id;
    new_token->type = ID;

    return new_token;
};

struct token *token_construct_symb(char symb) {
    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->id = (char*)
        many_atempts_calloc(MAX_ID_LEN,
                            sizeof(char),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token->id == NULL) {
        return NULL;
    }

    new_token->symb = symb;
    new_token->type = SYMB;

    return new_token;
}

int32_t token_destruct(struct token *token) {
    token->type = POISON_INT;
    token->number = POISON_INT;
    free(token->id);
    token->symb = POISON_CHAR;
    free(token);

    return 0;
};

int32_t token_dump(struct token token) {
    switch (token.type) {
        case NUMBER:
            printf("Number[%f]\n", token.number);
            break;
        case ID:
            printf("Id[%s]\n", token.id);
            break;
        case SYMB:
            printf("Symb[%c]\n", token.symb);
            break;
        case UNUSED:
            printf("Unused\n");
            break;
        default:
            printf("Bad token[%p]\n", &token);
            break;
    }

    return 0;
}

struct token *get_token_number(char *expression, 
                               int32_t start_index, int32_t *end_index) {
    double number = 0;
    char *get_number_enptr = NULL;
    get_number(expression, &number, start_index, &get_number_enptr);
    *end_index = index_in_string_by_char_ptr(expression,
                                             get_number_enptr) - 1;

    return token_construct_number(number);
}

struct token *get_token_id(char *expression,
                           int32_t start_index, int32_t *end_index) {
    char *id = NULL;
    get_word(expression, start_index, &id);
    *end_index = start_index + strlen(id) - 1;

    return token_construct_id(id);
}

struct token *get_token_symb(char *expression, int32_t symb_index) {
    return token_construct_symb(expression[symb_index]);
};

struct token *tokenize(char *expression) {
    if (expression == NULL)
        return NULL;

    struct token *token_arr = (struct token*)
        many_atempts_calloc(strlen(expression) + 1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    for (int32_t i = 0; i < strlen(expression) + 1; ++i) {
        token_arr[i] = *token_construct_unused();
    }

    char symb = '~';
    int32_t last_token_index = 0;

    for (int32_t symb_index = 0;
         symb_index < strlen(expression);
         ++symb_index) {
        symb = expression[symb_index];
        if (isdigit(symb)) {
            token_arr[last_token_index] = *get_token_number(expression,
                                                           symb_index,
                                                           &symb_index);
        } else if isalpha(symb) {
            
            token_arr[last_token_index] = *get_token_id(expression,
                                                       symb_index,
                                                       &symb_index);
        } else {        
            token_arr[last_token_index] = *get_token_symb(expression,
                                                          symb_index);
        }
        ++last_token_index;
        
    }

    return token_arr;
}

int32_t eval_expression(struct token *tokens, int32_t *cur_pos, double *result) {
    double my_result = 0;
    for (;
         tokens[*cur_pos].type != UNUSED;
         ++*cur_pos) {
        eval_term(tokens, cur_pos, &my_result);
        *result = *result + my_result;
    }

    return 0;
}

int32_t eval_term(struct token *tokens, int32_t *cur_pos, double *result) {
    struct token token = tokens[*cur_pos];
    double my_result = 0;
    if (token.type == NUMBER) {
        my_result = token.number;
    } else if (token.type == SYMB) {
        if (token.symb == '-') {
            *cur_pos = *cur_pos + 1;
            eval_term(tokens, cur_pos, &my_result);
            my_result = my_result * -1;
        } else  if (token.symb == '+') {
            *cur_pos = *cur_pos + 1;
            eval_term(tokens, cur_pos, &my_result);
        }
    }

    *result = my_result;
    return 0;
}

int32_t calculate(char *expression, double *result) {
    if (expression == NULL)
        return 0;

    struct token *tokens = tokenize(expression);

    for (int32_t token_index = 0;
         tokens[token_index].type != UNUSED;
         ++token_index) {
        printf("HI\n");
        eval_expression(tokens, &token_index, result);
    }

    return 0;
}
