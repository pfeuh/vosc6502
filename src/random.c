
#include "random.h"
#include <time.h>
#include <stdlib.h>

byte getrand(void)
{
    return rand();
}

void initrand(byte value)
{
    value++; // to fake the compiler
    srand(time(NULL));
}
