#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "general.h"
#include "calculator.h"

#define ARR_LEN(arr) sizeof(arr) / sizeof(arr[0])
int main() {
    struct token *token_arr = tokenize("3.5-15+1");
    for (int i = 0; i < 15; ++i) {
        token_dump(token_arr[i]);
    }
    double a = 32.012345678901234;
    char str[50];
    int b = 1000;
    gcvt(a, b, str);
    printf("%s\n", str);
    return 0;
}