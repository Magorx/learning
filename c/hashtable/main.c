#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "general.h"
#include "list.h"
#include "hashtable.h"

int main() {
    struct hashtable *table = hashtable_generate();
    hashtable_destruct(table);
    //hashtable_super_test("test.txt");
    return 0;
}
