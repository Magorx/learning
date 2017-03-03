#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "general.h"
#include "list.h"
#include "hashtable.h"

int main() {
    //hashtable_test_all();
    hashtable_count_most_used_words("test.txt");
    char *word = "ABcDEf";
    string_to_lower(&word, FALSE);
    printf("%s\n", word);
    return 0;
}
