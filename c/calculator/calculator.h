#ifndef CALCULATOR_H
#define CALCULATOR_H

extern const int32_t MAX_EXPRESSION_LEN;

/*  Grammar:
    Expr = Term + Expr | Term - Expr | Term
    Term = Factor * Term | Factor / Term | Factor
    Factor = Unit ^ Factor | Unit | -Factor | +Factor
    Unit = Number | (Expr) | UnaryFunction(Expr)
*/

struct token {
    int32_t type;
    double number;
    char *id;
    char symb;
};

int32_t calculate(char *expression, double *result);

#endif  // CALCULATOR_H
