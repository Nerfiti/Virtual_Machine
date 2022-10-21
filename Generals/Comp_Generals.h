#ifndef COMP_GENERALS_H
#define COMP_GENERALS_H

static const int maximum_cmd_length = 100;
static const int signature_length   = 12;
static const int cmd_id_mask        = (1 << 24) - 1; 
static const int number_of_regs     = 4;
static const int max_regname_len    = 3;

struct Header
{
    const char signature[signature_length] = "PDA";
    const int  version                      = 6;
};

#define DEF_CMD(cmd, num, ...) \
    CMD_##cmd = num,
enum cmd
{
    #include "cmds.h"
    NUM_CMDS
};
#undef DEF_CMD


#define DEF_CMD(cmd, num, ...) \
    #cmd,
const char cmds[NUM_CMDS][maximum_cmd_length + 1] = 
{
    "EMP",
    #include "cmds.h"
};
#undef DEF_CMD

const char regs[number_of_regs + 1][max_regname_len + 1] =
{
    "NUL",
    "RAX",
    "RBX",
    "RCX",
    "RDX"
};

enum Cmdmode
{
    Without_special_args = 0,
    With_RAM             = 1 << 28,
    With_REG             = 1 << 29,
    With_PLUS            = 1 << 30
};

#endif //COMP_GENERALS_H