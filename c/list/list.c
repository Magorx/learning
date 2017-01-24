#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "general.h"

struct list_node_data *const FICTIVE_NODE_DATA = (struct list_node_data*) 1;
char *const FICTIVE_NODE_DATA_KEY = "FICTIVE_DATA";

const int MAX_LIST_NODE_DATA_KEY_LEN = 30;
const int NODE_DUMP_COUNT = 6;
const int TEST_ITER_COUNT = 100;
const int SAMPLE_LIST_SIZE = 6;

//====list_node_data===========================================================
struct list_node_data *list_node_data_from_other(struct list_node_data *other) {
	if (other == FICTIVE_NODE_DATA)
		return other;
    if (list_node_data_ok(other) != 0)
        return NULL;

    return list_node_data_from_values(other->key, other->value);
};

struct list_node_data *list_node_data_from_values(char *key, int value) {
	if (key == NULL)
		return NULL;
	if (strlen(key) > MAX_LIST_NODE_DATA_KEY_LEN)
		return NULL;

	struct list_node_data *new_list_node_data = (struct list_node_data*)
		many_atempts_calloc(1,
						sizeof(struct list_node_data),
						MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_list_node_data == NULL) {
		return NULL;
	}

	char *new_key = (char*)
		many_atempts_calloc(MAX_LIST_NODE_DATA_KEY_LEN,
						sizeof(char),
						MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_key == NULL) {
		return NULL;
	}
	new_list_node_data->key = new_key;
	strcpy(new_list_node_data->key, key);
	new_list_node_data->value = value;
	return new_list_node_data;
}

int list_node_data_destruct(struct list_node_data *self) {
    if (list_node_data_ok(self) != 0)
        ERR_RETURN(ERR_ARG1);

    free(self->key);
	self->key = NULL;
    self->value = POISON_INT;
    free(self);
    return 0;
}

int list_node_data_ok(struct list_node_data *self) {
    if (self == NULL) {
        return ERR_NULL_OBJ;
    }
    if (self->key == NULL) {
        return ERR_LIST_NODE_DATA_KEY_BROKEN;
    }
	if (strlen(self->key) > MAX_LIST_NODE_DATA_KEY_LEN) {
		return ERR_BROKEN_DATA_KEY;
	}

    return 0;
}

int list_node_data_dump(struct list_node_data *self) {
	int status = list_node_data_ok(self);
    printf("list_node_data[%p] is %s\n", self,
			status? "broken" : "ok");

	if (status != 0) {
		ERR_RETURN(ERR_ARG1);
	}

    printf("key[%p]: %s\n", self->key, self->key);
    printf("value: %d\n", self->value);
    return 0;
}

int list_node_data_comparator(struct list_node_data *first, 
							  struct list_node_data *second) {
	if (list_node_data_ok(first) != 0 || list_node_data_ok(second) != 0) {
		return ERR_LIST_NODE_DATA_BROKEN;
	}
	if (strcmp(first->key, second->key)) {
		return FALSE;
	}
	if (first->value != second->value) {
		return FALSE;
	}
	return TRUE;
}

int list_node_data_test() {
	struct list_node_data *other = (struct list_node_data*)
		calloc(1, sizeof(struct list_node_data));
	other->key = (char*)calloc(100, sizeof(char));
	strcpy(other->key, "string");

	if (list_node_data_ok(other) != 0) {
		return ERR_LIST_NODE_DATA_BROKEN;
	}

	int i = 0;
	struct list_node_data *data = NULL;
	for (i = 0; i < 100; ++i) {
		printf("%d)\n", i);
		data = list_node_data_from_other(other);
		EXPECT_CMP_EQ(data, other, list_node_data_comparator);

		if (randint(1, 2) % 2) {
			strcpy(other->key, "normal_test");
		} else {
			strcpy(other->key, "tooooooooooooooooooooooo loooooong teeeeeest");
		}

		if (list_node_data_ok(data) != 0) {
			continue;
		}
		list_node_data_dump(data);
		list_node_data_destruct(data);
	}

	list_node_data_destruct(other);
	return 0;
}
//===== list_node ===============================================================

struct list_node *list_node_construct(struct list_node_data *data) {
	if (data == FICTIVE_NODE_DATA) {
		return list_node_construct_fictive();
	}
	if (list_node_data_ok(data) != 0)
		return NULL;
    struct list_node *new_node = NULL;
	new_node = (struct list_node*)
		many_atempts_calloc(1, sizeof(struct list_node), MAX_MEMORY_ALLOCATION_ATTEMPTS);
    if (new_node == NULL) {
        return NULL;
    }

    struct list_node_data *new_node_data = list_node_data_from_other(data);
    if (new_node_data == NULL) {
        return NULL;
    }
    new_node->data = new_node_data;

    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

struct list_node *list_node_construct_fictive() {
	struct list_node *new_node = NULL;
	new_node = (struct list_node*)
		many_atempts_calloc(1, sizeof(struct list_node), MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_node == NULL) {
		return NULL;
	}
	new_node->data = FICTIVE_NODE_DATA;
	return new_node;
}

int list_node_destruct(struct list_node *self) {
    if (list_node_ok(self) != 0)
        ERR_RETURN(ERR_ARG1);

    list_node_data_destruct(self->data);
    self->next = NULL;
    self->prev = NULL;
    free(self);
    return 0;
}

int list_node_ok(struct list_node *self) {
	if (self == NULL) {
		return ERR_NULL_OBJ;
	}
	if (list_node_is_fictive(self)) {
		return ERR_LIST_NODE_FICTIVE;
	}
	if (list_node_data_ok(self->data) != 0) {
		return ERR_LIST_NODE_DATA_BROKEN;
	}

	return 0;
}

int list_node_dump(struct list_node *self) {
	printf("==Start dumping list_node==\n");
	int status = list_node_ok(self);
    printf("list_node[%p] is %s\n", self,
        status ? "broken" : "ok");

    if (status != 0) {
        ERR_RETURN(ERR_ARG1);
    }

	list_node_data_dump(self->data);
	printf("===End dumping list_node===\n");
    return 0;
}

struct list_node *list_node_next(struct list_node *self) {
    if (list_node_ok(self) != 0)
        return NULL;
	if (list_node_is_fictive(self) == TRUE)
		return NULL;

    return self->next;
}

struct list_node *list_node_prev(struct list_node *self) {
	int status = 0;
	status = list_node_ok(self);

    if (status != 0 && status != ERR_LIST_NODE_FICTIVE)
        return NULL;

    return self->prev;
}

struct list_node_data *list_node_get_data(struct list_node *self) {
    if (list_node_ok(self) != 0)
        return NULL;

    return self->data;
}

int list_node_comparator(struct list_node *first,
						 struct list_node *second) {
	if (list_node_ok(first) != 0 || list_node_ok(second) != 0) {
		return FALSE;
	}
	if (list_node_data_comparator(first->data, second->data) != TRUE) {
		return FALSE;
	}
	if (list_node_next(first) != list_node_next(second)) {
		return FALSE;
	}
	if (list_node_prev(first) != list_node_prev(second)) {
		return FALSE;
	}
	return TRUE;
}

int list_node_is_fictive(struct list_node *self) {
	if (self == NULL)
		return FALSE;

	if (self->data == FICTIVE_NODE_DATA) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int list_node_test() {
	struct list_node_data *other = (struct list_node_data*)
		calloc(1, sizeof(struct list_node_data));
	other->key = (char*)calloc(MAX_LIST_NODE_DATA_KEY_LEN, sizeof(char));
	other->key = "string";
	other->value = 0;

	if (list_node_data_ok(other) != 0)
		return ERR_LIST_NODE_DATA_BROKEN;

	struct list_node *node = list_node_construct(other);
	if (list_node_ok(node) != 0)
		return ERR_LIST_NODE_BROKEN;

	int i = 0;
	struct list_node_data *data = NULL;
	node->next = node;
	node->prev = node;
	for (i = 0; i < 100; ++i) {
		data = list_node_data_from_other(other);
		printf("%d)\n", i);
		node = list_node_construct(data);
		node->next = node;
		node->prev = node;
		if (randint(0, 1)) {
			node->prev = NULL;
		}
		printf("[good_node_status] %d\n", list_node_ok(node));
		EXPECT_CMP_EQ(node, list_node_next(node), list_node_comparator);
		EXPECT_CMP_EQ(node, list_node_prev(node), list_node_comparator);
		data = list_node_get_data(node);
		printf("[data] %p\n", data);
		list_node_dump(node);
		if (i < 99) {
			list_node_destruct(node);
		}
	}
	
	list_node_dump(node);
	list_node_data_destruct(node->data);
	node->data = NULL;
	printf("[bad_node_status] %d\n", list_node_ok(node));
	list_node_destruct(node);
	list_node_dump(node);
	return 0;
}

//===list======================================================================
struct list *list_construct() {
	struct list *new_list = (struct list*)
		many_atempts_calloc(1, sizeof(struct list), MAX_MEMORY_ALLOCATION_ATTEMPTS);
	if (new_list == NULL) {
		return NULL;
	}

	new_list->fictive_node = list_node_construct_fictive();
	new_list->fictive_node->next = new_list->fictive_node;
	new_list->fictive_node->prev = new_list->fictive_node;
	new_list->size = 0;
	return new_list;
}

int list_destruct(struct list *self) {
	if (list_ok(self) != 0)
		ERR_RETURN(ERR_LIST_BROKEN);
	
	list_clear(self);
	self->size = POISON_INT;
	free(self->fictive_node);
	free(self);

	return 0;
}

int list_ok(struct list *self) {
	if (self == NULL) {
		return ERR_NULL_OBJ;
	}
	if (self->fictive_node == NULL) {
		return ERR_LIST_BROKEN;
	}
	if (self->size < 0) {
		return ERR_LIST_BROKEN;
	}

	struct list_node *node = self->fictive_node->next;
	int size = 0;
	int ok = 0;
	for (node = self->fictive_node->next;
		node != self->fictive_node;
		node = node->next) {
		++size;
		if (list_node_ok(node) != 0) {
			return ERR_LIST_NODE_BROKEN;
		}
	}
	if (size != self->size) {
		return ERR_LIST_BROKEN;
	}

	return 0;
}

int list_dump(struct list *self) {
	printf("== Start dumping list ==\n");
	int status = list_ok(self);
	printf("List[%p] is %s\n", self, status ? "broken" : "ok");

	if (status != 0) {
		ERR_RETURN(ERR_ARG1);
	}

	printf("Fictive node: [%p]\n", self->fictive_node);
	printf("Size: %d\n", self->size);
	if (list_size(self) <= NODE_DUMP_COUNT) {
		printf("Nodes:\n\n");
		struct list_node *node = list_begin(self);
		for (node = list_begin(self);
			 node != list_end(self);
			 node = list_node_next(node)) {
			list_node_dump(node);
		}
	} else {
		printf("Front:\n\n");
		struct list_node *node = list_begin(self);
		int i = 0;
		for (i = 0; i < NODE_DUMP_COUNT / 2; ++i) {
			list_node_dump(node);
			node = list_node_next(node);
			printf("\n");
		}
		printf("Back:\n\n");
		node = list_end(self);
		for (i = 0; i < NODE_DUMP_COUNT / 2; ++i) {
			list_node_dump(node);
			node = list_node_prev(node);
			printf("\n");
		}
	}
	printf("=== End dumping list ===\n");
	return 0;
}

int list_empty(struct list *self) {
	if (list_ok(self) != 0)
		ERR_RETURN (ERR_LIST_BROKEN);
	
	if (list_size(self) == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int list_size(struct list *self) {
	if (list_ok(self) != 0)
		ERR_RETURN(ERR_LIST_BROKEN);

	return self->size;
}

int list_insert(struct list *self,					
				struct list_node_data *data,	
				struct list_node *pos) {
	if (list_ok(self) != 0)
		ERR_RETURN(ERR_LIST_BROKEN);

	struct list_node *new_node = list_node_construct(data);
	if (new_node == NULL) {
		ERR_RETURN(ERR_FAILED_NODE_CREATING);
	}

	struct list_node *prev = list_node_prev(pos);
	prev->next = new_node;
	new_node->prev = prev;
	new_node->next = pos;
	pos->prev = new_node;
	++self->size;
	return 0;
}

int list_push_back(struct list *self, struct list_node_data *new_data) {
	return list_insert(self, new_data, list_end(self));
}

int list_push_front(struct list *self, struct list_node_data *new_data) {
	return list_insert(self, new_data, list_begin(self));
}

int list_erase(struct list *self, struct list_node *pos) {
	if (list_ok(self) != 0)
		ERR_RETURN (ERR_LIST_BROKEN);

	struct list_node *prev = list_node_prev(pos);
	struct list_node *next = list_node_next(pos);
	
	prev->next = next;
	next->prev = prev;
	list_node_destruct(pos);
	--self->size;
	
	return 0;
}

int list_pop_back(struct list *self) {
	return list_erase(self, list_node_prev(list_end(self)));
}

int list_pop_front(struct list *self) {
	return list_erase(self, list_begin(self));
}

int list_clear(struct list *self) {
	if (list_ok(self) != 0)
		ERR_RETURN(ERR_LIST_BROKEN);

	while (list_size(self) > 0) {
		list_pop_back(self);
	}

	return 0;
}

struct list_node *list_begin(struct list *self) {
	if (list_ok(self) != 0)
		return NULL;

	return self->fictive_node->next;
}

struct list_node *list_end(struct list *self) {
	if (list_ok(self) != 0)
		return NULL;

	return self->fictive_node;
}

struct list_node_data *list_front(struct list *self) {
	if (list_ok(self) != 0)
		return NULL;

	return list_node_get_data(list_begin(self));
}

struct list_node_data *list_back(struct list *self) {
	if (list_ok(self) != 0)
		return NULL;

	return list_node_get_data(list_node_prev(list_end(self)));
}

struct list_node *list_find(struct list *self,
							struct list_node_data *data_to_find) {
	if (list_ok(self) != 0)
		return NULL;

	struct list_node *node = NULL;
	int attempt_counter = 0;
	for (node = list_begin(self);
		 node != list_end(self);
		 node = list_node_next(node)) {
		if (list_node_data_comparator(list_node_get_data(node),
									  data_to_find) == TRUE) {
			break;
		}
	}

	return node;
}

//==Testing_list===============================================================
int test_list_ConstructDestruct() {
	struct list *list = NULL;
	int i = 0;
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		list = list_construct();
		if (list == NULL) {
			break;
		}
		ASSERT_EQ(list_ok(list), 0);
		list_destruct(list);
	}

	return 0;
}

int test_list_EmptySizeClear() {
	struct list *list = list_construct();
	ASSERT_EQ(list_ok(list), 0);
	ASSERT_EQ(list_empty(list), TRUE);
	ASSERT_EQ(list_size(list), 0);

	int i = 0;
	int count = 0;
	struct list_node_data *data = NULL;
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		data = list_node_data_from_values("some_key", randint(-100, 100));
		list_push_back(list, data);
		count += 1;
		ASSERT_EQ(list_ok(list), 0);
		ASSERT_EQ(list_empty(list), FALSE);
		ASSERT_EQ(list_size(list), count);
		if (i % (TEST_ITER_COUNT / 10) == 0) {
			list_clear(list);
			ASSERT_EQ(list_ok(list), 0);
			ASSERT_EQ(list_empty(list), TRUE);
			ASSERT_EQ(list_size(list), 0);
			count = 0;
		}
	}
	list_destruct(list);

	return 0;
}

struct list *list_generate() {
	struct list *list = list_construct();
	if (list == NULL) {
		return NULL;
	}
	int i = 0;
	char *str = NULL;
	for (i = 0; i < SAMPLE_LIST_SIZE; ++i) {
		randstr(randint(5, 20), &str);
		list_push_back(list,
					   list_node_data_from_values(str, randint(-100, 100)));
	}
	return list;
}

int test_list_Ok() {
	struct list *list = list_generate();
	int i = 0;
	ASSERT_EQ(list_ok(list), 0);
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		list->fictive_node = NULL;
		ASSERT_EQ(list_ok(list), ERR_LIST_BROKEN);
		list = list_generate();
		list->size = -5;
		ASSERT_EQ(list_ok(list), ERR_LIST_BROKEN);
		list = list_generate();
		list->fictive_node->next->data = NULL;
		ASSERT_EQ(list_ok(list), ERR_LIST_NODE_BROKEN);
		list = list_generate();
	}
	return 0;
}

int test_list_InsertPush() {
	struct list *list = list_generate();
	int i = 0;
	struct list_node *node = list_begin(list);
	for (i = 0; i < SAMPLE_LIST_SIZE / 2; ++i) {
		node = list_node_next(node);
	}
	struct list_node_data *data = NULL;
	int count = SAMPLE_LIST_SIZE / 2;
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		data = list_node_data_from_values("insert_data", randint(-100, 100));
		list_insert(list, data, node);
		++count;
		ASSERT_CMP_EQ(list_node_get_data(list_node_prev(node)),
					  data, 
					  list_node_data_comparator);
		list_push_front(list, data);
		ASSERT_CMP_EQ(list_node_get_data(list_begin(list)),
					  data, 
					  list_node_data_comparator);
		list_push_back(list, data);
		ASSERT_CMP_EQ(list_node_get_data(list_node_prev(list_end(list))),
					  data,
					  list_node_data_comparator);
	}
	list_destruct(list);
	return 0;
}

int test_list_ErasePop() {
	struct list *list = NULL;
	int i = 0;
	int count = 0;
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		list = list_generate();
		count = list_size(list);
		list_pop_front(list);
		--count;
		ASSERT_EQ(list_size(list), count);
		list_erase(list, list_node_next(list_node_next(list_begin(list))));
		--count;
		ASSERT_EQ(list_size(list), count);
		list_pop_back(list);
		--count;
		ASSERT_EQ(list_size(list), count);
		list_destruct(list);
	}
	return 0;
} 

int test_list_Find() {
	struct list *list = list_generate();
	struct list_node *node = NULL;
	struct list_node *node_found = NULL;
	struct list_node_data *data = NULL;

	node = list_node_next(list_node_next(list_begin(list)));
	struct list_node_data *data_to_find = list_node_get_data(node);

	int i = 0;
	for (i = 0; i < TEST_ITER_COUNT; ++i) {
		data = list_node_data_from_values("test_find", randint(-100, 100));
		list_push_front(list, data);
		node_found = list_find(list, data);
		ASSERT_CMP_EQ(node_found, list_begin(list), list_node_comparator);
		node_found = list_find(list, data_to_find);
		ASSERT_CMP_EQ(node, node_found, list_node_comparator);
	}

	list_destruct(list);
	return 0;
}

int list_test() {
	test_list_Ok();
	test_list_ConstructDestruct();
	test_list_EmptySizeClear();
	test_list_InsertPush();
	test_list_ErasePop();
	test_list_Find();

	return 0;
}
