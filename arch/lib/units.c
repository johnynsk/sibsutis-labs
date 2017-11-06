#include "units.h"

void CU()
{
    int8_t inst_curr = 0;
    sc_instGet(&inst_curr);
    sc_instSet(++inst_curr);
}
