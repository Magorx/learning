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

struct token *tokenize(char *expression) {
    if (expression == NULL)
        return NULL;

    struct token *token_arr = (struct token*)
        many_atempts_calloc(strlen(expression),
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    for (int32_t i = 0; i < strlen(expression); ++i) {
        token_arr[i] = *token_construct_unused();
    }

    char symb = '~';
    int32_t symb_index = 0;
    int32_t last_token_index = 0;
    int32_t symbols_to_ignore = 0;

    double number = 0;
    char *id = NULL;

    for (symb_index = 0; symb_index < strlen(expression); ++symb_index) {
        if (symbols_to_ignore > 0) {
            --symbols_to_ignore;
            continue;
        }

        symb = expression[symb_index];
        if (isdigit(symb)) {
            get_number(expression, symb_index, &number);
            token_arr[last_token_index] = *token_construct_number(number);
            //token_dump(token_arr[last_token_index]);
            ++last_token_index;
            symbols_to_ignore = strlen(tmp_string);
            continue;
        }

        if isalpha(symb) {
            get_word(expression, symb_index, &id);
            token_arr[last_token_index] = *token_construct_id(id);
            //token_dump(token_arr[last_token_index]);
            ++last_token_index;
            symbols_to_ignore = strlen(id) - 1;
            continue;
        }
        
        token_arr[last_token_index] = *token_construct_symb(symb);
        //token_dump(token_arr[last_token_index]);
        ++last_token_index;
        
    }

    return token_arr;
}

int32_t get_expression(struct token *tokens, int32_t *cur_pos, double *result) {
    //for (int32_t token_index = *cur_pos; )
    return 0;
}
