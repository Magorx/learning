#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "list.h"
#include "hashtable.h"

const int TEST_TABLE_SIZE = 1000;
const int TEST_ELEM_COUNT = 100;

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

    struct list **data = (struct list**)
        many_attempts_calloc(table_size,
                             sizeof(struct list),
                             MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (data == NULL) {
        return NULL;
    }

    int i = 0;
    struct list *new_list = NULL;
    for (i = 0; i < table_size; ++i) {
        new_list = list_construct();
        if (new_list == NULL) {
            return NULL;
        }
        data[i] = new_list;
    }

    new_hashtable->data = data;
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
        list_destruct(self->data[i]);
    }
    free(self->data);

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
        return ERR_HASHTABLE_NULL_DATA;
    }
    if (self->hash_function == NULL) {
        return ERR_HASHTABLE_HASH_FUNCTION_BROKEN;
    }
    if (self->elem_count < 0) {
        return ERR_HASHTABLE_ELEM_COUNT_BROKEN;
    }
    if (self->table_size < 0) {
        return ERR_HASHTABLE_TABLE_SIZE_BROKEN;
    }

    int i = 0;
    int true_elem_count = 0;
    for (i = 0; i < self->table_size; ++i) {
        if (list_ok(self->data[i]) != 0) {
            printf("[list_err] %d\n", list_ok(self->data[i]));
            return ERR_HASHTABLE_DATA_LIST_BROKEN;
        }
        true_elem_count = true_elem_count + list_size(self->data[i]);
    }
    if (true_elem_count != self->elem_count) {
        return ERR_HASHTABLE_ELEM_COUNT_BROKEN;
    }

    return 0;
}

int hashtable_dump(struct hashtable *self) {
    int status = hashtable_ok(self);
    printf("hashtable[%p] is %s\n", self, status ? "broken" : "ok");
    if (status != 0) {
        return ERR_HASHTABLE_BROKEN;
    }

    printf("data: %p\n", self->data);
    printf("table_size: %d\n", hashtable_table_size(self));
    printf("elem_count: %d\n", hashtable_size(self));
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

    return self->elem_count == 0 ? TRUE : FALSE;
};

int hashtable_hash(struct hashtable *self, struct user_data *data) {
    if (user_data_ok(data) != 0)
        return ERR_ARG1;

    return self->hash_function(data) % self->table_size;
};

/*int hashtable_standard_hash_function(struct user_data *data) {
    if (user_data_ok(data) != 0)
        ERR_RETURN(ERR_ARG1);

    return strlen(data->key);
}*/

int hashtable_standard_hash_function(struct user_data *data) {
    if (user_data_ok(data) != 0)
        ERR_RETURN(ERR_ARG1);

    int hash = 0;
    char *key = data->key;
    int symb_index = 0;
    for (symb_index = 0; symb_index < strlen(key); ++symb_index) {
        hash += key[symb_index];
    }
    
    return hash > 0 ? hash : 0;
}

int hashtable_insert(struct hashtable *self, struct user_data *data) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;
    if (user_data_ok(data) != 0)
        return ERR_ARG2;

    struct user_data *data_found = hashtable_find(self, data);
    if (data_found != NULL) {
        ++data_found->value;
    } else {
        int hash = hashtable_hash(self, data);
        struct user_data *data_to_insert = user_data_from_values(data->key, 1);
        list_push_back(self->data[hash], data_to_insert);
        ++self->elem_count;
    }

    return 0;
};

int hashtable_erase(struct hashtable *self, struct user_data *data) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;
    if (user_data_ok(data) != 0)
        return ERR_ARG2;

    struct user_data *data_found = hashtable_find(self, data);
    if (data_found == NULL) {
        return ERR_HASHTABLE_DATA_NOT_EXIST;
    }
    int hash = hashtable_hash(self, data);
    struct list *list = self->data[hash];
    list_erase(list, list_find(list, data));
    --self->elem_count;

    return 0;
};

int hashtable_clear(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return ERR_ARG1;

    int i = 0;
    for (i = 0; i < self->table_size; ++i) {
        list_clear(self->data[i]);
    }
    self->elem_count = 0;

    return 0;
}

struct list_node *_hashtable_find_node(struct hashtable *self,
                                       struct user_data *data_to_find) {
    if (hashtable_ok(self) != 0)
        return NULL;
    if (user_data_ok(data_to_find) != 0)
        return NULL;

    int hash = hashtable_hash(self, data_to_find);
    struct list *list = self->data[hash];
    struct list_node *node = list_find(list, data_to_find);
    
    return  node == list_end(list) ? NULL : node;
}

struct user_data *hashtable_find(struct hashtable *self,
                                       struct user_data *data_to_find) {
    struct list_node *node = _hashtable_find_node(self, data_to_find);
    return node == NULL ? NULL : list_node_get_data(node);
}

int hashtable_contains(struct hashtable *self, struct user_data *data_to_find) {
    if (hashtable_ok(self) != 0)
        return FALSE;
    if (user_data_ok(data_to_find) != 0)
        return FALSE;

    return hashtable_find(self, data_to_find) == NULL ? FALSE : TRUE;
}

//=============================================================================
struct hashtable *hashtable_generate() {
    struct hashtable *new_hashtable  = 
        hashtable_construct(TEST_TABLE_SIZE, hashtable_standard_hash_function);
    if (new_hashtable == NULL) {
        return NULL;
    }
    int i = 0;
    char *key = NULL;
    struct user_data *data = NULL;
    for (i = 0; i < TEST_ELEM_COUNT; ++i) {
        randstr(randint(1, 20), &key);
        data = user_data_from_values(key, randint(-100, 100));
        hashtable_insert(new_hashtable, data);
    }
    return new_hashtable;
};

int hashtable_test_ConstructDestruct() {
    struct hashtable *hash_table = NULL;
    int i = 0;
    for (i = 0; i < 1; ++i) {
        hash_table = hashtable_construct(TEST_TABLE_SIZE,
                                         hashtable_standard_hash_function);
        ASSERT_EQ(hashtable_ok(hash_table), 0);
        ASSERT_EQ(hashtable_destruct(hash_table), 0);
        hash_table = hashtable_generate();
        ASSERT_EQ(hashtable_ok(hash_table), 0);
        ASSERT_EQ(hashtable_destruct(hash_table), 0);
    }
    return 0;
};

int hashtable_test_Ok() {
    struct hashtable *hash_table = hashtable_generate();
    int i = 0;
    for (i = 0; i < TEST_ITER_COUNT; ++i) {
        hash_table = hashtable_generate();
        hash_table->data = NULL;
        ASSERT_EQ(hashtable_ok(hash_table), ERR_HASHTABLE_NULL_DATA);
        hash_table = hashtable_generate();
        hash_table->elem_count = hash_table->elem_count - 10;
        ASSERT_EQ(hashtable_ok(hash_table), ERR_HASHTABLE_ELEM_COUNT_BROKEN);
        hash_table = hashtable_generate();
        hash_table->table_size = -1;
        ASSERT_EQ(hashtable_ok(hash_table), ERR_HASHTABLE_TABLE_SIZE_BROKEN);
        hash_table = hashtable_generate();
        hash_table->hash_function = NULL;
        ASSERT_EQ(hashtable_ok(hash_table), ERR_HASHTABLE_HASH_FUNCTION_BROKEN);
    }

    return 0;
};

int hashtable_test_SizeTablesizeEmptyClear() {
    struct hashtable *hash_table = hashtable_generate();
    int elem_count = hash_table->elem_count;
    int table_size = hash_table->table_size;
    int i = 0;
    char *key = NULL;
    randstr(randint(1, 20), &key);
    struct user_data *data = user_data_from_values(key, randint(-100, 100));
    for (i = 0; i < TEST_ITER_COUNT; ++i) {
        ASSERT_EQ(hashtable_table_size(hash_table), table_size);
        ASSERT_EQ(hashtable_size(hash_table), elem_count);
        hashtable_insert(hash_table, data);
        elem_count = elem_count + 1;
        randstr(randint(1, 20), &key);
        data = user_data_from_values(key, randint(-100, 100));
        if (i % 10 == 0) {
            hashtable_clear(hash_table);
            ASSERT_EQ(hashtable_empty(hash_table), TRUE);
            hashtable_destruct(hash_table);
            hash_table = hashtable_generate();
            elem_count = hashtable_size(hash_table);
            table_size = hashtable_table_size(hash_table);
        }
    }

    return 0;
};

int hashtable_test_Hash() {
    /*
    This method must work, or else nothing more would work. But everything 
    works.
    */
    return 0;
};

int hashtable_test_InsertErase() {
    struct hashtable *hash_table = hashtable_generate();
    
    int i = 0;
    char *key = NULL;
    struct user_data *data = NULL;
    for (i = 0; i < TEST_ITER_COUNT; ++i) {
        randstr(randint(1, 20), &key);
        data = user_data_from_values(key, randint(-100, 100));
        ASSERT_EQ(hashtable_insert(hash_table, data), 0);
        ASSERT_EQ(hashtable_erase(hash_table, data), 0);
    }

    hashtable_destruct(hash_table);
    return 0;
};

int hashtable_test_Contains() {
    struct hashtable *hash_table = hashtable_generate();
    struct user_data *inserted_datas = (struct user_data*)
        many_attempts_calloc(TEST_ITER_COUNT, 
                             sizeof(struct user_data),
                             MAX_MEMORY_ALLOCATION_ATTEMPTS);
    struct user_data *data = NULL;
    char *key = NULL;

    int i = 0;
    for (i = 0; i < TEST_ITER_COUNT; ++i) {
        randstr(randint(1, 20), &key);
        data = user_data_from_values(key, randint(-100, 100));
        hashtable_insert(hash_table, data);
        inserted_datas[i] = *data;
    }
    for (i = 0; i < TEST_ITER_COUNT; ++i) {
        ASSERT_EQ(hashtable_contains(hash_table, &inserted_datas[i]), TRUE);
    }
    hashtable_destruct(hash_table);

    return 0;
}

int hashtable_test_all() {
    hashtable_test_Ok();
    hashtable_test_ConstructDestruct();
    hashtable_test_InsertErase();
    hashtable_test_SizeTablesizeEmptyClear();
    hashtable_test_Contains();
    hashtable_test_Hash();

    return 0;
}

struct user_data *hashtable_max_value_elem(struct hashtable *self) {
    if (hashtable_ok(self) != 0)
        return NULL;
   
    int i = 0;
    char *key = (char*)
        many_attempts_calloc(30, sizeof(char), MAX_MEMORY_ALLOCATION_ATTEMPTS);
    strcpy(key, "key");
    struct list *list = NULL;
    struct list_node *node = NULL;
    struct user_data *data = NULL;
    struct user_data *max_value_data = user_data_from_values(key, -1);

    for (i = 0; i < self->table_size; ++i) {
        //printf("%d\n[data_status] %d\n", i, user_data_ok(data));
        list = self->data[i];
        for (node = list_begin(list);
             node != list_end(list);
             node = list_node_next(node)) {
            data = list_node_get_data(node);
            if (data->value > max_value_data->value) {
                max_value_data = data;
            }
        }
    }

    return max_value_data;
}

int hashtable_count_most_used_words(const char *file_name, 
                                    int top_words_count) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return ERR_FILE_NOT_EXIST;
    }
    struct hashtable *hash_table = 
        hashtable_construct(1000, hashtable_standard_hash_function);
    if (hash_table == NULL) {
        return ERR_NULL_OBJ;
    }

    char *word = (char*)
        many_attempts_calloc(SMALL_BUFFER_LENGTH,
                             sizeof(char),
                             MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (word == NULL) {
        return ERR_STRING_NOT_CREATED;
    }

    int word_count = 0;
    struct user_data *data = NULL;
    int symb_index = 0;
    int symb_int = getc(file);
    char symb = '!';

    while (symb_int != EOF) {
        symb = (char)symb_int;
        if isspace(symb) {
            word_count += 1;
            if (word_count % 1000 == 0) {
                if (word_count % 10000 == 0) {
                    printf("==");
                }
                if (word_count % 100000 == 0) {
                    printf("==");
                }
                printf("%d words loaded\n", word_count);
            }
            normalize_string(&word, TRUE, SMALL_BUFFER_LENGTH);
            if (strlen(word)) {
                struct user_data *data = user_data_from_values(word, 0);
                hashtable_insert(hash_table, data);
            }

            empty_string(word);
            symb_index = 0;
        } else {
            word[symb_index] = symb;
            ++symb_index;
        }
        symb_int = getc(file);
    }

    int i = 0;
    for (i = 0; i < top_words_count; ++i) {
        data = hashtable_max_value_elem(hash_table);
        printf("[MAX_%d] %s %d\n", i + 1, data->key, data->value);
        hashtable_erase(hash_table, data);
    }

    fclose(file);
    free(word);
    hashtable_destruct(hash_table);
    return 0;
}
