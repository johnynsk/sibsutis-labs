#include "lib/memory.h"
#include "lib/registers.h"
#include "lib/errors.h"
#include "lib/command.h"
#include <stdio.h>

int main ()
{
    sc_memoryInit();

    printf("works well");
    return 0;
}
