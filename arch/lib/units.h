#include "registers.h"
#include "command.h"
#include "memory.h"
#include <stdbool.h>
void CU();
int ALU(int command, int operand);

int command_id(const char * command_name);
const char * command_name(int command_id);

//only for tests

int command_read(int operand);
int command_write(int operand);

int command_load(int operand);
int command_store(int operand);

int command_add(int operand);
int command_sub(int operand);
int command_divide(int operand);
int command_mul(int operand);

int command_jump(int operand);
int command_jneg(int operand);
int command_jz(int operand);
int command_halt();

int command_not(int operand);
int command_and(int operand);
int command_or(int operand);
int command_xor(int operand);
int command_jns(int operand);
int command_jc(int operand);
int command_jnc(int operand);
int command_jp(int operand);
int command_jnp(int operand);
int command_chl(int operand);
int command_shr(int operand);
int command_rcl(int operand);
int command_rcr(int operand);
int command_neg(int operand);
int command_addc(int operand);
int command_subc(int operand);
int command_loglc(int operand);
int command_logrc(int operand);
int command_rccl(int operand);
int command_rccr(int operand);
int command_mova(int operand);
int command_movr(int operand);
int command_movca(int operand);
int command_movcr(int operand);
int command_addc1(int operand);
int command_subc1(int operand);
