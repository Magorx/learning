#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "calculator.h"

#define DEBUG_MODE false

int main() {
    printf("Testing calculator\n");
    test_all();
    printf("All tests pased correctly\n");

    return 0;
}
