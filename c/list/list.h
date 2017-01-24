#ifndef LIST_H
#define LIST_H

enum LIST_ERRORS {
	ERR_LIST_NODE_BROKEN = -100,
	ERR_LIST_NODE_DATA_KEY_BROKEN,
	ERR_LIST_NODE_DATA_BROKEN,
	ERR_LIST_NODE_BRROKEN,
	ERR_LIST_BROKEN,
	ERR_FAILED_NODE_CREATING,
	ERR_BROKEN_DATA_KEY,
	ERR_LIST_NODE_FICTIVE,
};

extern const int MAX_LIST_NODE_DATA_KEY_LEN;
extern const int NODE_DUMP_COUNT;
extern const int TEST_ITER_COUNT;
extern const int SAMPLE_LIST_SIZE;

//=== list_node_data ==========================================================
struct list_node_data {
    char *key;
    int value;
};

struct list_node_data *list_node_data_from_other(struct list_node_data *other);
struct list_node_data *list_node_data_from_values(char *key, int value);
int list_node_data_destruct(struct list_node_data *self);
int list_node_data_ok(struct list_node_data *self);
int list_node_data_dump(struct list_node_data *self);
int list_node_data_comparator(struct list_node_data *val_1, 
							  struct list_node_data *val_2);

int list_node_data_test();

//=== list_node ===============================================================
struct list_node {
    struct list_node *prev;
    struct list_node *next;
    struct list_node_data *data;
};

struct list_node *list_node_construct(struct list_node_data *data);
struct list_node *list_node_construct_fictive();
int list_node_destruct(struct list_node *self);
int list_node_ok(struct list_node *self);
int list_node_dump(struct list_node *self);
int list_node_comparator(struct list_node *val_1, struct list_node *val_2);

int list_node_is_fictive(struct list_node *self);

struct list_node *list_node_next(struct list_node *self);
struct list_node *list_node_prev(struct list_node *self);
struct list_node_data *list_node_get_data(struct list_node *self);

int list_node_test();

//=== list ====================================================================
struct list {
    int size;
    struct list_node *fictive_node;
};

struct list *list_construct();
int list_destruct(struct list *self);
int list_ok(struct list *self);
int list_dump(struct list *self);

int list_empty(struct list *self);
int list_size(struct list *self);

int list_insert(struct list *self,
				struct list_node_data *data,
				struct list_node *pos);
int list_push_back(struct list *self, struct list_node_data *data);
int list_push_front(struct list *self, struct list_node_data *new_data);
int list_erase(struct list *self, struct list_node *pos);
int list_pop_back(struct list *self);
int list_pop_front(struct list *self);
int list_clear(struct list *self);

struct list_node *list_begin(struct list *self);
struct list_node *list_end(struct list *self);
struct list_node_data *list_front(struct list *self);
struct list_node_data *list_back(struct list *self);

struct list_node *list_find(struct list *self,
							struct list_node_data *data_to_find);

int test_list_ConstructDestruct();
int test_list_Ok();
int test_list_InsertPush();
int test_list_ErasePop();
int test_list_EmptySizeClear();
int test_list_Find();
int list_test();

#endif  // LIST_H
