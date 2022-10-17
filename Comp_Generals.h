#ifndef COMP_GENERALS_H
#define COMP_GENERALS_H

static const int maximum_cmd_length = 10;
static const int signature_length   = 12;
static const int num_cmds           = 16;

struct Header
{
    const char signature[signature_length] = "PDA";
    const int  version                      = 6;
};

enum cmd
{
    CMD_PUSH = 1,
    CMD_ADD  = 2,
    CMD_SUB  = 3,
    CMD_MUL  = 4,
    CMD_DIV  = 5,
    CMD_DUP  = 6,
    CMD_OUT  = 7,
    CMD_JMP  = 8,
    CMD_JB   = 9,
    CMD_JBE  = 10,
    CMD_JA   = 11,
    CMD_JAE  = 12,
    CMD_JE   = 13,
    CMD_JNE  = 14,
    CMD_POP  = 15,
    CMD_HLT  = 16
};

const char cmds[num_cmds + 1][maximum_cmd_length + 1] = 
{
    "EMP",
    "PUSH",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "DUP",
    "OUT",
    "JMP",
    "JB",
    "JBE",
    "JA",
    "JAE",
    "JE",
    "JNE",
    "POP",
    "HLT"
};

#endif //COMP_GENERALS_H