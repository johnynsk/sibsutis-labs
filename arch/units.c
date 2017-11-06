#include "units.h"

void CU()
{
    int inst_curr = 0;
    sc_instGet(&inst_curr);
    int memory_curr;
    sc_instSet(++inst_curr);
}
