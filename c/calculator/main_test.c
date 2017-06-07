#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "calculator.h"

#define DEBUG_MODE false

int main() {
    printf("Testing calculator\n");
    test_all();
    printf("All tests passed correctly\n");

    return 0;
}
