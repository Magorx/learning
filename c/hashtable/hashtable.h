#ifndef HASHTABLE_H
#define HASHTABLE_H
enum HASHTABLE_ERRORS {
    ERR_HASHTABLE_BROKEN = -100,
    ERR_HASHTABLE_DATA_BROKEN,
    ERR_HASHTABLE_TABLE_SIZE_BROKEN,
    ERR_HASHTABLE_ELEM_COUNT_BROKEN,
    ERR_HASHTABLE_HASH_FUNCTION_BROKEN,
    ERR_HASHTABLE_DATA_NOT_EXIST,
};

struct hashtable {
	int (*hash_function)(struct user_data*);
	struct list *data;
	int table_size;
	int elem_count;
};

struct hashtable *hashtable_construct(int table_size, int (*hash_function)(struct user_data*));
int hashtable_destruct(struct hashtable *self);
int hashtable_ok(struct hashtable *self);
int hashtable_dump(struct hashtable *self);

int hashtable_size(struct hashtable *self);
int hashtable_table_size(struct hashtable *self);
int hashtable_empty(struct hashtable *self);

int hashtable_hash(struct hashtable *self, struct user_data *data);

int hashtable_insert(struct hashtable *self, struct user_data *data);
int hashtable_erase(struct hashtable *self, struct user_data *data);
int hashtable_clear(struct hashtable *self);

int hashtable_contains(struct hashtable *self, struct user_data *data_to_find);

#endif  // HASHTABLE_H INCLUDED