#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "calculator.h"

const int32_t NUMBER = 1;
const int32_t ID = 2;
const int32_t SYMB = 3;
const int32_t UNUSED = 4;
const int32_t MAX_ID_LEN = 20;
const int32_t MAX_EXPRESSION_LEN = 1000;

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

int32_t token_destruct(struct token token) {
    if (token.type == ID) {
        free(token.id);
    }

    token.type = POISON_INT;
    token.number = POISON_INT;
    token.symb = POISON_CHAR;

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

int32_t write_token_unused_to_ptr(struct token *ptr) {
    struct token *token = token_construct_unused();
    *ptr = *token;
    free(token);

    return 0;
}

int32_t read_token_number_to_ptr(char *expression, int32_t *start_index,
                                       struct token *ptr) {
    double number = 0;
    char *get_number_endptr = NULL;
    get_number(expression, &number, *start_index, &get_number_endptr);
    *start_index = index_in_string_by_char_ptr(expression,
                                               get_number_endptr) - 1;
    struct token *token = token_construct_number(number);
    *ptr = *token;
    free(token);

    return 0;
}

int32_t read_token_id_to_ptr(char *expression, int32_t *start_index,
                                   struct token *ptr) {
    char *id = NULL;
    get_word(expression, *start_index, &id);
    *start_index = *start_index + strlen(id) - 1;

    struct token *token = token_construct_id(id);
    *ptr = *token;
    free(token);

    return 0;
}

int32_t read_token_symb_to_ptr(char *expression, int32_t *symb_index, 
                                     struct token *ptr) {
    struct token *token = token_construct_symb(expression[*symb_index]);
    *ptr = *token;
    free(token);

    return 0;
};

struct token *tokenize(char *expression) {
    if (expression == NULL)
        return NULL;

    struct token *token_arr = (struct token*)
        many_atempts_calloc(strlen(expression) + 1,
                            sizeof(struct token),
                            MAX_MEMORY_ALLOCATION_ATTEMPTS);
    for (int32_t i = 0; i < strlen(expression) + 1; ++i) {
        write_token_unused_to_ptr(&token_arr[i]);
    }

    char symb = 0;
    int32_t last_token_index = 0;

    for (int32_t symb_index = 0;
         symb_index < strlen(expression);
         ++symb_index) {
        symb = expression[symb_index];
        if (isspace(symb)) {
            if (symb == ' ') {
                continue;
            } else {
                break;
            }
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
    printf("expr pos %d\n", *cur_pos);

    double cur_result = 0;
    eval_term(tokens, cur_pos, &cur_result);

    struct token token = tokens[*cur_pos];
    
    while (token.type == SYMB && (token.symb == '+' || token.symb == '-')) {
        ++*cur_pos;
        double tmp_result = 0;
        eval_term(tokens, cur_pos, &tmp_result);
        switch (token.symb) {
            case '+':
                cur_result = cur_result + tmp_result;
                break;
            case '-':
                cur_result = cur_result - tmp_result;
                break;
        }

        token = tokens[*cur_pos];
    }

    *result = cur_result;
    return 0;
}

int32_t eval_term(struct token *tokens, int32_t *cur_pos, double *result) {
    printf("term pos %d\n", *cur_pos);

    double cur_result = 0;
    eval_factor(tokens, cur_pos, &cur_result);

    struct token token = tokens[*cur_pos];
    while (token.type == SYMB && (token.symb == '*' || token.symb == '/')) {
        ++*cur_pos;
        double tmp_result = 0;
        switch (token.symb) {
            case '*':
                eval_factor(tokens, cur_pos, &tmp_result);
                cur_result = cur_result * tmp_result;
                break;
            case '/':
                eval_factor(tokens, cur_pos, &tmp_result);
                cur_result = cur_result / tmp_result;
                break;
        }

        token = tokens[*cur_pos];
    }

    *result = cur_result;
    return 0;
}

int32_t eval_factor(struct token *tokens, int32_t *cur_pos, double *result) {
    printf("fact pos %d\n", *cur_pos);

    double tmp_result = 0;
    struct token token = tokens[*cur_pos];

    if (token.type == NUMBER) {
        eval_unit(tokens, cur_pos, &tmp_result);
    } else if (token.type == SYMB) {
        switch (token.symb) {
            case '+':
                ++*cur_pos;
                eval_factor(tokens, cur_pos, &tmp_result);
                break;
            case '-':
                ++*cur_pos;
                eval_factor(tokens, cur_pos, &tmp_result);
                tmp_result = tmp_result * -1;
                break;
            case '(':
                eval_unit(tokens, cur_pos, &tmp_result);
        }
    } else if (token.type == ID) {
        eval_unit(tokens, cur_pos, &tmp_result);
    }
    *result = tmp_result;

    token = tokens[*cur_pos];
    if (token.type == SYMB && token.symb == '^') {
        ++*cur_pos;
        eval_factor(tokens, cur_pos, &tmp_result);
        printf("HI\n");
        *result = pow(*result, tmp_result);
    }

    return 0;
}

int32_t eval_unit(struct token *tokens, int32_t *cur_pos, double *result) {
    printf("unit pos %d\n", *cur_pos);

    struct token token = tokens[*cur_pos];

    if (token.type == NUMBER) {
        *result = token.number;
        ++*cur_pos;
        return 0;
    }

    if (token.type == SYMB && token.symb == '(') {
        ++*cur_pos;
        eval_expression(tokens, cur_pos, result);
        ++*cur_pos;
    }

    if (token.type == ID) {
        ++*cur_pos;
        eval_expression(tokens, cur_pos, result);
        handle_function(token.id, *result, result);
    }

    return 0;
}


int32_t handle_function(char *function, double arg, double *result) {
    if (function == NULL)
        return ERR_NULL_OBJ;

    printf("func %s(%f)\n", function, arg);
    if (strcmp(function, "sqrt") == 0) {
        *result = sqrt(arg);
    }
    if (strcmp(function, "exp") == 0) {
        *result = exp(arg);
    }
    if (strcmp(function, "sin") == 0) {
        *result = sin(arg);
    }
    if (strcmp(function, "cos") == 0) {
        *result = cos(arg);
    }
    if (strcmp(function, "log") == 0) {
        *result = log(arg);
    }
    if (strcmp(function, "lg") == 0) {
        *result = log10(arg);
        printf("%f\n", *result);
    }
    if (strcmp(function, "abs") == 0) {
        *result = fabs(arg);
    }
    if (strcmp(function, "round") == 0) {
        *result = round(arg);
    }
    if (strcmp(function, "trunc") == 0) {
        *result = trunc(arg);
    }
    if (strcmp(function, "") == 0) {
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

    int32_t DEBUG = FALSE;
    if (DEBUG == TRUE) {
         for (int i = 0; i < strlen(expression); ++i) {
            token_dump(tokens[i]);
        }
    }

    int32_t cur_pos = 0;
    eval_expression(tokens, &cur_pos, result);

    for (int i = 0; i < strlen(expression); ++i) {
        token_destruct(tokens[i]);
    }
    free(tokens);

    return 0;
}
