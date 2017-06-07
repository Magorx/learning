#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "general.h"
#include "calculator.h"

#define DEBUG_MODE false

int main() {
    printf("Enter your expression: ");
    char *str = many_atempts_calloc(sizeof(char),
                                    MAX_EXPRESSION_LEN, 
                                    MAX_MEMORY_ALLOCATION_ATTEMPTS);
    fgets(str, MAX_EXPRESSION_LEN, stdin);

    DEBUG printf("===== DEBUG =====\n");
    double res = 0;
    calculate(str, &res);
    DEBUG printf("=================\n");
    printf("result: %f\n", res);

    free(str);

    return 0;
}
