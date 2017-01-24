#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "general.h"


int main() {
	srand(time(NULL));

	list_test();
	char *str;
	randstr(10, &str);
	printf("%s\n", str);

    return 0;
}
