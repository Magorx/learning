#ifndef LIST_H
#define LIST_H

enum LIST_ERRORS {
	ERR_LIST_NODE_BROKEN = -100,
	ERR_USER_DATA_KEY_BROKEN,
	ERR_USER_DATA_BROKEN,
	ERR_LIST_NODE_BRROKEN,
	ERR_LIST_BROKEN,
	ERR_FAILED_NODE_CREATING,
	ERR_BROKEN_DATA_KEY,
	ERR_LIST_NODE_FICTIVE,
};

extern const int MAX_user_data_KEY_LEN;
extern const int NODE_DUMP_COUNT;
extern const int TEST_ITER_COUNT;
extern const int SAMPLE_LIST_SIZE;

//=== user_data ==========================================================
struct user_data {
    char *key;
    int value;
};

struct user_data *user_data_from_other(struct user_data *other);
struct user_data *user_data_from_values(char *key, int value);
int user_data_destruct(struct user_data *self);
int user_data_ok(struct user_data *self);
int user_data_dump(struct user_data *self);
int user_data_comparator(struct user_data *first, 
							  struct user_data *second);

int user_data_test();

//=== list_node ===============================================================
struct list_node {
    struct list_node *prev;
    struct list_node *next;
    struct user_data *data;
};

struct list_node *list_node_construct(struct user_data *data);
struct list_node *list_node_construct_fictive();
int list_node_destruct(struct list_node *self);
int list_node_ok(struct list_node *self);
int list_node_dump(struct list_node *self);
int list_node_comparator(struct list_node *first, struct list_node *second);

int list_node_is_fictive(struct list_node *self);

struct list_node *list_node_next(struct list_node *self);
struct list_node *list_node_prev(struct list_node *self);
struct user_data *list_node_get_data(struct list_node *self);

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
				struct user_data *data,
				struct list_node *pos);
int list_push_back(struct list *self, struct user_data *data);
int list_push_front(struct list *self, struct user_data *data);
int list_erase(struct list *self, struct list_node *pos);
int list_pop_back(struct list *self);
int list_pop_front(struct list *self);
int list_clear(struct list *self);

struct list_node *list_begin(struct list *self);
struct list_node *list_end(struct list *self);
struct user_data *list_front(struct list *self);
struct user_data *list_back(struct list *self);

struct list_node *list_find(struct list *self,
							struct user_data *data_to_find);

int test_list_ConstructDestruct();
int test_list_Ok();
int test_list_InsertPush();
int test_list_ErasePop();
int test_list_EmptySizeClear();
int test_list_Find();
int list_test();

#endif  // LIST_H
