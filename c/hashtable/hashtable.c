#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"
#include "general.h"

int func(struct user_data *user data){
    return user_data->value;
}

struct hashtable *hashtable_construct(int table_size,
                                      int (*hash_function)(struct user_data*)) {
    if (size < 0)
        return NULL
    struct new_hashtable = many_attempts_calloc
}