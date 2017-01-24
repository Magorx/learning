#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "general.h"

struct stack *stack_construct(int size) {
    int *data_pointer = (int*) calloc(size, sizeof(int));
    int attempt_count = 0;

    for (attempt_count = 0; attempt_count < 5; ++attempt_count) {
        if (data_pointer) {
            break;
        }
        ++attempt_count;
        size /= 2;
        data_pointer = (int*) calloc(size, sizeof(int));
    }

    struct stack *new_stack = (struct stack*) calloc(size, sizeof(int));
    for (attempt_count = 0; attempt_count < 5; attempt_count++) {
        if (new_stack) {
            break;
        }
        ++attempt_count;
        new_stack = (struct stack*) calloc(size, sizeof(int));
    }

    if (data_pointer == NULL || new_stack == NULL) {
        return NULL;
    }

    new_stack->data = data_pointer;
    new_stack->max_size = size;
    new_stack->size = 0;
    return new_stack;
}

int stack_destruct(struct stack *stack) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);
    int i = 0;
    for (i = 0; i < stack->max_size; ++i) {
        stack->data[i] = POISON_int;
    }
    free(stack->data);

    stack->size = POISON_int;
    stack->max_size = POISON_int;

    free(stack);
    return 0;
}

//==================================================

int stack_ok(struct stack *stack) {
    if (stack->size < 0 || stack->size > stack->max_size) {
        return ERR_STACK_SIZE;
    }
    return 0;
}


int stack_dump(struct stack *stack) {
    printf("=============================\n");
    printf("stack[%p] is %s\n", stack, stack_ok(stack) ? "broken":"ok");
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);
    printf("max size %d\n", stack->max_size);
    printf("filled %d\n\n", stack->size);

    int size = 20;
    if (size > stack->size) {
        size = stack->size;
    }
    int i = 0;
    for (i = 0; i < size; ++i) {
        printf("[%3d] %d\n", i, stack->data[i]);
    }

    printf("=============================\n");
    return 0;
}

int stack_size(struct stack *stack) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    return stack->size;
}

int stack_empty(struct stack *stack) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    if (stack_size(stack) == 0) {
        return TRUE;
    }
    return FALSE;
}


int stack_full(struct stack *stack) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    if (stack_size(stack) == stack->max_size) {
        return TRUE;
    }
    return FALSE;
}


int stack_clean(struct stack *stack) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    int i = 0;
    for (i = 0; i < stack->size; ++i) {
        stack->data[i] = 0;
    }
    stack->size = 0;
    return 0;
}

int stack_push(struct stack *stack, int push_arg) {
   if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    if (stack->size == stack->max_size) {
        ERR_RETURN(ERR_STACK_FULL);
    }
    stack->data[stack->size] = push_arg;
    stack->size++;
    return 0;
}

int stack_pop(struct stack *stack, int *pop_arg) {
    if (stack_ok(stack) != 0) ERR_RETURN(ERR_ARG1);

    if (stack_empty(stack)) {
        ERR_RETURN(ERR_STACK_EMPTY);
    }
    *pop_arg = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;
    return 0;
}

//============================================

const int SIZE = 10;

int test_stack(struct stack *stack) {
    printf("Creating stack\n");
    stack = stack_construct(SIZE);
    int num = 0;
    int i = 0;

    printf("Filling stack\n");
    for (i = 0; i < SIZE; ++i) {
        num = randint(10) + 1;
        stack_push(stack, num);
    }

    printf("[Full] %s\n", stack_full(stack) == TRUE? "TRUE":"FALSE");
    stack_pop(stack, &num);
    printf("%d poped\n", num);
    printf("[Full] %s\n", stack_full(stack) == TRUE? "TRUE":"FALSE");
    printf("[Empty] %s\n", stack_empty(stack) == TRUE? "TRUE":"FALSE");

    printf("Dumping stack\n");
    stack_dump(stack);

    printf("Cleaning stack\n");
    stack_clean(stack);

    printf("[Empty] %s\n", stack_empty(stack) == TRUE? "TRUE":"FALSE");

    printf("Destructing stack\n");
    stack_destruct(stack);

    printf("End\n");
    return 0;
}
