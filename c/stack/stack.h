#ifndef STACK_H
#define STACK_H

enum STACK_ERRORS {
    ERR_STACK_FULL = -100,
    ERR_STACK_SIZE,
    ERR_STACK_EMPTY,
    ERR_STACK_NOT_CREATED,
};

struct stack {
    int *data;
    int size;
    int max_size;
};

struct stack *stack_construct(int size);
int stack_destruct(struct stack *stack);
int stack_ok(struct stack *stack);
int stack_dump(struct stack *stack);

int stack_size(struct stack *stack);
int stack_empty(struct stack *stack);
int stack_full(struct stack *stack);

int stack_clean(struct stack *stack);
int stack_push(struct stack *stack, int push_arg);
int stack_pop(struct stack *stack, int *pop_arg);

int test_stack(struct stack *stack);

#endif // STACK_H
