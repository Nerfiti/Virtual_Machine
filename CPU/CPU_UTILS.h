#ifndef CPU_UTILS_H
#define CPU_UTILS_H

#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <math.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"
#include "SolveEquation.h"

#include "stack.h"

const int number_of_registers = 5;
const int size_of_ram         = 1 << 18;

//#define ON_DUMP
#ifdef ON_DUMP
    #define DUMP_ON(code) code
#else
    #define DUMP_ON(code)
#endif //ON_DUMP

struct SoftCPU
{
    Header *head                 = nullptr;
    int *code                    = nullptr;
    int IP                       = 0;
    stack_id main_stk            = 0;
    FILE *result                 = nullptr;
    int reg[number_of_registers] = {};
    int ram[size_of_ram]         = {};
    stack_id ret_stk             = 0;
};

void init_CPU    (SoftCPU *CPU);
void execute_CPU (SoftCPU *CPU);
void CheckHead   (Header head);
void SegFault    ();
void Dump        (SoftCPU *CPU);
void Paint       (int max_symbols, int window_width, int window_height, int *video_memory);
int *ProcArgsPushAndPop (int command, SoftCPU *CPU, int *args, bool pop);

#endif //CPU_UTILS_H