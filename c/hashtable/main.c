#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "list.h"
#include "hashtable.h"

int main() {
    hashtable_count_most_used_words("test.txt", 100);
    return 0;
}
