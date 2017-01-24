#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    struct stack *stack = NULL;
    test_stack(stack);
    return 0;
}
