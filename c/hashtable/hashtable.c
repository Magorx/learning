#include <stdlib.h>
#include <stdio.h>
#include "general.h"
#include "list.h"
#include "hashtable.h"


struct hashtable *hashtable_construct(int table_size,
                                      int (*hash_function)(struct user_data*)) {
    if (table_size < 0)
        return NULL;

    struct hashtable *new_hashtable = (struct hashtable*)
        many_attempts_calloc(1,
                             sizeof(struct hashtable),
                             MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_hashtable == NULL) {
        return NULL;
    }

    new_hashtable->data = (struct list*)
        many_attempts_calloc(table_size,
                             sizeof(struct list),
                             MAX_MEMORY_ALLOCATION_ATTEMPTS);
    int i = 0;
    for (i = 0; i < table_size; ++i) {
        new_hashtable->data[i] = *list_construct();
    }

    new_hashtable->hash_function = hash_function;
    new_hashtable->table_size = table_size;
    new_hashtable->elem_count = 0;
    return new_hashtable;
};

int hashtable_destruct(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;

    int i = 0;
    for (i = 0; i < self->table_size; ++i) {
        list_destruct(&self->data[i]);
    }
    self->table_size = POISON_INT;
    self->elem_count = POISON_INT;
    self->hash_function = NULL;
    free(self);
    return 0;
};

int hashtable_ok(struct hashtable *self) {
    if (self == NULL) {
        return ERR_NULL_OBJ;
    }
    if (self->data == NULL) {
        return ERR_HASHTABLE_DATA_BROKEN;
    }
    if (self->hash_function == NULL) {
        return ERR_HASHTABLE_HASH_FUNCTION_BROKEN;
    }
    if (self->elem_count < 0) {
        return ERR_HASHTABLE_ELEM_COUNT_BROKEN;
    }
    int i = 0;
    int size_count = 0;
    for (i = 0; i < self->table_size; ++i) {
        if (list_ok(&self->data[i]) != 0) {
            return ERR_HASHTABLE_DATA_BROKEN;
        }
        size_count = size_count + list_size(&self->data[i]);
    }
    if (size_count != self->elem_count) {
        return ERR_HASHTABLE_ELEM_COUNT_BROKEN;
    }
    if (self->table_size < 0) {
        return ERR_HASHTABLE_TABLE_SIZE_BROKEN;
    }

    return 0;
}

int hashtable_dump(struct hashtable *self) {
    int status = hashtable_ok(self);
    printf("hashtable[%p] is %s\n", self, status ? "broken" : "ok");
    if (status != 0){
        return ERR_HASHTABLE_BROKEN;
    }

    printf("data: %p\n", self->data);
    printf("table_size: %d\n", self->table_size);
    printf("elem_count: %d\n", self->table_size);
    return 0;
}

int hashtable_size(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;

    return self->elem_count;
};

int hashtable_table_size(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;

    return self->table_size;
};

int hashtable_empty(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return FALSE;

    if (self->elem_count == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
};

int hashtable_hash(struct hashtable *self, struct user_data *data) {
    if (user_data_ok(data) != 0)
        return ERR_ARG1;

    return self->hash_function(data) % self->table_size;
};

int hashtable_insert(struct hashtable *self, struct user_data *data) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;
    if (user_data_ok(data) != 0)
        return ERR_ARG2;

    int key = hashtable_hash(self, data);
    struct list *list = &self->data[key];
    if (hashtable_contains(self, data) == TRUE) {
        struct list_node *node = list_find(list, data);
        node->data = node->data + 1;
    } else {
        list_push_back(list, data);
        struct list_node *node = list_node_prev(list_end(list));
        node->data->value = 1;
        self->elem_count = self->elem_count + 1;
    }

    return 0;
};

int hashtable_erase(struct hashtable *self, struct user_data *data) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;
    if (user_data_ok(data) != 0)
        return ERR_ARG2;

    int key = hashtable_hash(self, data);
    if (hashtable_contains(self, data) == FALSE) {
        return ERR_HASHTABLE_DATA_NOT_EXIST;
    }
    struct list *list = &self->data[key];
    list_erase(list, list_find(list, data));

    return 0;
};

int hashtable_clear(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;

    int i = 0;
    for (i = 0; i < self->table_size; ++i) {
        list_clear(&self->data[i]);
    }

    return 0;
}

int hashtable_contains(struct hashtable *self, struct user_data *data_to_find) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;
    if (user_data_ok(data_to_find) != 0)
        return ERR_ARG2;

    int key = hashtable_hash(self, data_to_find);
    struct list *list = &self->data[key];
    if (list_find(list, data_to_find) == list_end(list)) {
        return FALSE;
    } else {
        return TRUE;
    }
}