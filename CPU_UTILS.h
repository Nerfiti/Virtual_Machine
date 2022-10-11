#ifndef CPU_UTILS_H
#define CPU_UTILS_H

#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"
#include "stack.h"

extern const int   version_CPU;
extern const char *input_filename;
extern const char *output_filename;

const int number_of_registers = 5;

struct SoftCPU
{
    Header *head      = nullptr;
    int *code         = nullptr;
    int IP            = 0;
    stack_id main_stk = 0;
    FILE *result      = nullptr;
    int reg[number_of_registers] = {};
};

void init_CPU   (SoftCPU *CPU);
void execute_CPU(SoftCPU *CPU);

#endif //CPU_UTIL_H