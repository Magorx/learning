#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.h"
#include "hashtable.h"
#include "general.h"

int main() {
    struct hashtable *table = hashtable_generate();
    table = NULL;
    hashtable_test_all();
    return 0;
}
