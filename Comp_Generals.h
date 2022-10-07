#ifndef COMP_GENERALS_H
#define COMP_GENERALS_H

static const int maximum_cmd_length = 4;
static const int signature_length   = 4;
static const int num_cmds           = 7;

struct Header
{
    const char signature[signature_length] = "PDA";
    const int version                      = 1;
    long long numbers_of_the_commands      = 0;
};

enum cmd
{
    CMD_PUSH = 1,
    CMD_ADD  = 2,    //a + b
    CMD_SUB  = 3,    //a - b
    CMD_MUL  = 4,    //a * b
    CMD_DIV  = 5,    //a / b
    CMD_OUT  = 6,    //print
    CMD_HLT  = 7     // end
};

const char cmds[num_cmds + 1][maximum_cmd_length + 1] = 
{
    "EMP",
    "PUSH",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "OUT",
    "HLT"
};

#endif //COMP_GENERALS_H