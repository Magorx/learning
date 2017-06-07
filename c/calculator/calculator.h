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

/**
 * @brief Calculate expression.
 * @details Calculates exression, stores result to result.
 * 
 * @param expression your expression
 * @param result where to store result
 * 
 * @return error code
 */
int32_t calculate(char *expression, double *result);

/**
 * @brief Tests all calculator's capabilities
 * @details calculates every type of expression, print ASSERT_EQ_FAILED if
 *          some of them don't work.
 *          
 * @return 0
 */
int32_t test_all();

#endif  // CALCULATOR_H
