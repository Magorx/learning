#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "general.h"
#include "calculator.h"

#define ARR_LEN(arr) sizeof(arr) / sizeof(arr[0])
int main() {
    printf("Enter your expression: ");
    char *str = many_atempts_calloc(sizeof(char),
                                    MAX_EXPRESSION_LEN, 
                                    MAX_MEMORY_ALLOCATION_ATTEMPTS);
    fgets(str, MAX_EXPRESSION_LEN, stdin);

    printf("===== DEBUG =====\n");
    double res = 0;
    calculate(str, &res);
    printf("=================\n");
    printf("result: %f\n", res);

    free(str);

    int32_t a = 5;
    printf("a = %d\n", a);

    return 0;
}
