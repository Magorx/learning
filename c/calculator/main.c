#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "calculator.h"

#define DEBUG_MODE false

int main(int32_t argc, char *argv[]) {
    DEBUG printf("===== DEBUG =====\n");
    double res = 0;
    if (argc == 1) {
        printf("Enter your expression: ");
        char *str = many_atempts_calloc(sizeof(char),
                                        MAX_EXPRESSION_LEN, 
                                        MAX_MEMORY_ALLOCATION_ATTEMPTS);
        fgets(str, MAX_EXPRESSION_LEN, stdin);
        calculate(str, &res);
        printf("result: %f\n", res);
        free(str);
    } else {
        char *str = NULL;
        join_strings(&argv[1], argc - 1, &str);
        calculate(str, &res);
        printf("result: %f\n", res);
    }
    DEBUG printf("=================\n");

    return 0;
}
