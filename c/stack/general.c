#include <stdlib.h>
#include "general.h"

const int POISON_int = -123;
const int TRUE = 1;
const int FALSE = 0;

int randint(int num) {
    return rand() % num;
}
