#ifndef COMP_GENERALS_H
#define COMP_GENERALS_H

static const int maximum_cmd_length = 10;
static const int signature_length   = 12;

struct Header
{
    const char signature[signature_length] = "PDA";
    const int  version                      = 6;
};

#define DEF_CMD(cmd, num) \
    CMD_##cmd = num,
enum cmd
{
    #include "cmds.h"
    NUM_CMDS
};
#undef DEF_CMD


#define DEF_CMD(cmd, num) \
    #cmd,
const char cmds[NUM_CMDS][maximum_cmd_length + 1] = 
{
    "EMP",
    #include "cmds.h"
};
#undef DEF_CMD

#endif //COMP_GENERALS_H