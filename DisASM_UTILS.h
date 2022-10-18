#ifndef DISASM_UTILS_H
#define DISASM_UTILS_H

#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"

extern const int   version_ASM;
extern const char *input_filename;
extern const char *output_filename;

struct DisASM
{
    Header *head      = nullptr;
    int *code         = nullptr;
    int IP            = 0;
};

void init_ASM   (DisASM *disasm);
void execute_ASM(DisASM *disasm);
void CheckHead  (Header head);

#endif //DISASM_UTILS_H