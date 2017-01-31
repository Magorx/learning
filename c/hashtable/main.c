#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.h"
#include "hashtable.h"
#include "general.h"

int main() {
	srand(time(NULL));

	struct hashtable *table = hashtable_generate();
    hashtable_dump(table);
	//randstr(10, &str);
	//printf("%s\n", str);

    return 0;
}
