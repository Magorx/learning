#ifndef CALCULATOR_H
#define CALCULATOR_H

extern const int32_t NUMBER;
extern const int32_t ID;
extern const int32_t SYMB;
extern const int32_t UNUSED;
extern const int32_t MAX_ID_LEN;
extern const int32_t MAX_EXPRESSION_LEN;

/*  Grammar:
    Expr = Term + Expr | Term - Expr | Term
    Term = Factor * Term | Factor / Term | -Term | +Term | Factor
    Factor = Unit ^ Factor | Unit
    Unit = Number | (Expr) | UnaryFunction(Expr)
*/

struct token {
    int32_t type;
    double number;
    char *id;
    char symb;
};

struct token *token_construct_unused();
struct token *token_construct_number(double number);
struct token *token_construct_id(char *id);
struct token *token_construct_symb(char symb);
int32_t token_destruct(struct token *token);
int32_t token_dump(struct token token);

struct token *tokenize(char *expression);

int32_t eval_expression(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_term(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_factor(struct token *tokens, int32_t *cur_pos, double *result);
int32_t eval_unit(struct token *tokens, int32_t *cur_pos, double *result);

int32_t calculate(char *expression, double *result);

#endif  // CALCULATOR_H
