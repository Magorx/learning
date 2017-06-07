#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "calculator.h"

#define DEBUG_MODE false

const int32_t EMPTY = 0;
const int32_t NUMBER = 1;
const int32_t ID = 2;
const int32_t SYMB = 3;
const int32_t MAX_ID_LEN = 20;
const int32_t MAX_EXPRESSION_LEN = 1000;

const int32_t ERR_ID_NOT_CREATED = -100;

int32_t eval_expression(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_term(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_factor(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_unit(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_function(char *function, double arg, double *result);

struct token *token_construct_empty() {
    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->type = EMPTY;

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

    new_token->type = NUMBER;
    new_token->number = number;

    return new_token;
};

struct token *token_construct_id(char *id) {
    if (id == NULL) {
        return NULL;
    }

    struct token *new_token = (struct token*)
        many_atempts_calloc(1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token == NULL) {
        return NULL;
    }

    new_token->id = (char*)
        many_atempts_calloc(strlen(id),
                            sizeof(char),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_token->id == NULL) {
        free(new_token);
        return NULL;
    }

    new_token->type = ID;
    strcpy(new_token->id, id);

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

    new_token->type = SYMB;
    new_token->symb = symb;

    return new_token;
}

int32_t token_clear(struct token *token) {
    if (token == NULL) {
        return ERR_NULL_OBJ;
    }
    if (token->type == ID) {
        free(token->id);
    }

    token->id = NULL;
    token->type = 0;
    token->number = 0;
    token->symb = 0;

    return 0;
};

int32_t token_destruct(struct token *token) {
    if (token == NULL) {
        return ERR_NULL_OBJ;
    }

    if (token->type == ID) {
        free(token->id);
    }

    token->type = POISON_INT;
    token->number = POISON_INT;
    token->id = NULL;
    token->symb = POISON_CHAR;
    free(token);

    return 0;
}

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
        case EMPTY:
            printf("Unused\n");
            break;
        default:
            printf("Bad token[%p]\n", &token);
            break;
    }

    return 0;
}

int32_t read_token_number_to_ptr(char *expression, int32_t *start_index,
                                 struct token *ptr) {
    char *endptr = NULL;
    double number = strtod(&expression[*start_index], &endptr);
    *start_index = endptr - expression;

    struct token token;
    token_clear(&token);
    token.type = NUMBER;
    token.number = number;
    *ptr = token;

    return 0;
}

int32_t read_token_id_to_ptr(char *expression, int32_t *start_index,
                             struct token *ptr) {
    char *id = get_word(&expression[*start_index], NULL);
    *start_index = *start_index + strlen(id);

    struct token token;
    token.type = ID;
    token.id = (char*)
        many_atempts_calloc(MAX_ID_LEN,
                            sizeof(char),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (token.id == NULL) {
        return ERR_ID_NOT_CREATED;
    }
    strcpy(token.id, id);
    *ptr = token;

    return 0;
}

int32_t read_token_symb_to_ptr(char *expression, int32_t *symb_index, 
                                     struct token *ptr) {
    struct token token;
    token_clear(&token);
    token.type = SYMB;
    token.symb = expression[*symb_index];
    *ptr = token;
    ++*symb_index;

    return 0;
};

struct token *tokenize(char *expression) {
    if (expression == NULL)
        return NULL;
    int32_t expr_len = strlen(expression);

    struct token *token_arr = (struct token*)
        many_atempts_calloc(expr_len + 1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (token_arr == NULL)
        return NULL;

    int32_t symb_index = 0;
    int32_t last_token_index = 0;
    while (symb_index < expr_len) {
        char symb = 0;
        symb = expression[symb_index];
        if (symb == ' ') {
            ++symb_index;
            continue;
        }
        if (isspace(symb)) {
            break;
        }

        if (isdigit(symb)) {
            read_token_number_to_ptr(expression, &symb_index,
                                     &token_arr[last_token_index]);
        } else if isalpha(symb) {
            read_token_id_to_ptr(expression, &symb_index, 
                                 &token_arr[last_token_index]);
        } else {        
            read_token_symb_to_ptr(expression, &symb_index, 
                                   &token_arr[last_token_index]);
        }

        ++last_token_index;
    }

    return token_arr;
}

int32_t eval_expression(struct token *tokens, int32_t *cur_pos, double *result) {
    DEBUG printf("expr pos %d\n", *cur_pos);

    double cur_result = 0;
    eval_term(tokens, cur_pos, &cur_result);

    struct token token = tokens[*cur_pos];
    while (token.type == SYMB && (token.symb == '+' || token.symb == '-')) {
        ++*cur_pos;
        double tmp_result = 0;
        eval_term(tokens, cur_pos, &tmp_result);
        if (token.symb == '+') {
                cur_result = cur_result + tmp_result;
        } else {
                cur_result = cur_result - tmp_result;
                break;
        }

        token = tokens[*cur_pos];
    }

    *result = cur_result;
    return 0;
}

int32_t eval_term(struct token *tokens, int32_t *cur_pos, double *result) {
    DEBUG printf("term pos %d\n", *cur_pos);

    double cur_result = 0;
    eval_factor(tokens, cur_pos, &cur_result);

    struct token token = tokens[*cur_pos];
    while (token.type == SYMB && (token.symb == '*' || token.symb == '/')) {
        ++*cur_pos;
        double tmp_result = 0;
        eval_factor(tokens, cur_pos, &tmp_result);
        if (token.symb == '*') {
            cur_result = cur_result * tmp_result;
        } else {
            cur_result = cur_result / tmp_result;
        }

        token = tokens[*cur_pos];
    }

    *result = cur_result;
    return 0;
}

int32_t eval_factor(struct token *tokens, int32_t *cur_pos, double *result) {
    DEBUG printf("fact pos %d\n", *cur_pos);

    double tmp_result = 0;
    
    struct token token = tokens[*cur_pos];
    if (token.type == SYMB && (token.symb == '+' || token.symb == '-')) {
        ++*cur_pos;
        eval_factor(tokens, cur_pos, &tmp_result);
        if (token.symb == '-') {
                tmp_result = -tmp_result;
        }

        *result = tmp_result;
        return 0;
    } else {
        eval_unit(tokens, cur_pos, &tmp_result);
    }
    *result = tmp_result;

    token = tokens[*cur_pos];
    if (token.type == SYMB && token.symb == '^') {
        ++*cur_pos;
        eval_factor(tokens, cur_pos, &tmp_result);
        *result = pow(*result, tmp_result);
    }

    return 0;
}

int32_t eval_unit(struct token *tokens, int32_t *cur_pos, double *result) {
    DEBUG printf("unit pos %d\n", *cur_pos);

    struct token token = tokens[*cur_pos];
    ++*cur_pos;

    if (token.type == NUMBER) {
        *result = token.number;
        return 0;
    }

    if (token.type == SYMB && token.symb == '(') {
        eval_expression(tokens, cur_pos, result);
        ++*cur_pos;
    }

    if (token.type == ID) {
        ++*cur_pos;
        eval_expression(tokens, cur_pos, result);
        eval_function(token.id, *result, result);
    }

    return 0;
}


int32_t eval_function(char *function, double arg, double *result) {
    if (function == NULL)
        return ERR_NULL_OBJ;

    DEBUG printf("func %s(%f)\n", function, arg);

    if (strcmp(function, "sqrt") == 0) {
        *result = sqrt(arg);
    } else if (strcmp(function, "exp") == 0) {
        *result = exp(arg);
    } else if (strcmp(function, "sin") == 0) {
        *result = sin(arg);
    } else if (strcmp(function, "cos") == 0) {
        *result = cos(arg);
    } else if (strcmp(function, "log") == 0) {
        *result = log(arg);
    } else if (strcmp(function, "lg") == 0) {
        *result = log10(arg);
    } else if (strcmp(function, "abs") == 0) {
        *result = fabs(arg);
    } else if (strcmp(function, "round") == 0) {
        *result = round(arg);
    } else if (strcmp(function, "trunc") == 0) {
        *result = trunc(arg);
    } else if (strcmp(function, "") == 0) {
        *result = 0;
    }

    return 0;
}

int32_t calculate(char *expression, double *result) {
    if (expression == NULL)
        return ERR_ARG1;
    if (result == NULL)
        return ERR_ARG2;

    struct token *tokens = tokenize(expression);
    int32_t expr_len = strlen(expression);

    int32_t cur_pos = 0;
    eval_expression(tokens, &cur_pos, result);

    for (int i = 0; i < expr_len; ++i) {
        token_clear(&tokens[i]);
    }
    free(tokens);

    return 0;
}


int32_t test_all() {
    double res = 0;
    
    calculate("0", &res);
    ASSERT_EQ(res, 0);
    calculate("-1", &res);
    ASSERT_EQ(res, -1);
    calculate("2 + 3", &res);
    ASSERT_EQ(res, 5);
    calculate("2 - 3", &res);
    ASSERT_EQ(res, -1);
    calculate("2 * 3", &res);
    ASSERT_EQ(res, 6);
    calculate("2 * 0", &res);
    ASSERT_EQ(res, 0);
    calculate("2 * 0", &res);
    ASSERT_EQ(res, 0);
    calculate("2^3", &res);
    ASSERT_EQ(res, 8);
    calculate("2^1", &res);
    ASSERT_EQ(res, 2);
    calculate("2^0", &res);
    ASSERT_EQ(res, 1);
    calculate("2^-2", &res);
    ASSERT_EQ(res, 0.25);
    calculate("(0)", &res);
    ASSERT_EQ(res, 0);
    calculate("2 + (1 + 2)", &res);
    ASSERT_EQ(res, 5);
    calculate("(1 - 1) + (2 + 3)", &res);
    ASSERT_EQ(res, 5);
    calculate("2 - (1 + 2)", &res);
    ASSERT_EQ(res, -1);
    calculate("2 + -(1 + 2)", &res);
    ASSERT_EQ(res, -1);
    calculate("-(1)", &res);
    ASSERT_EQ(res, -1);
    calculate("(2)^(3)", &res);
    ASSERT_EQ(res, 8);
    calculate("2 * lg(10)", &res);
    ASSERT_EQ(res, 2);
    calculate("2 ^ abs(-3)", &res);
    ASSERT_EQ(res, 8);

    return 0;
}