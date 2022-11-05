#ifndef ASM_UTILS_H
#define ASM_UTILS_H

#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"

extern const Header head;
const int label_arr_size = 100;

struct label
{
    int value = 0;
    char name[maximum_cmd_length] = "";  
};

struct ASM_t
{
    Text input_data = {};
    
    int index = 0;
    label label_arr[label_arr_size] = {};

    int *code = nullptr;
    int ip    = 0;
};

enum Regs
{
    Wrong_Reg = -1,
    RAX       =  1,
    RBX       =  2,
    RCX       =  3,
    RDX       =  4
};


typedef char ProgMode;
enum ProgramMode 
{
    WrongMode = 1 << 0,
    O9        = 1 << 1
};


char getProgramMode  (const int argc, const char *argv[]);
int  ProcArgsGetMode (ASM_t ASM, char *args_line, int *args, int *argc, bool first_assemble);
void init_ASM        (ASM_t *ASM);
int  execute_ASM     (ASM_t *ASM, bool first_assemble);
void optimizeExecute (ASM_t *ASM);
int  SearchName      (ASM_t ASM, char *name);
void PrintListing    (FILE *listing_file, char *asm_line, int *code, int argc);
void PrintHeader     (FILE* listing_file);
void DelComment      (char *line, char comm_symbol);
void SetLabel        (ASM_t *ASM, char *command, int value);
void PrintCode       (int *code, int code_len);
int  GetRegNum       (char *reg_name);
void ASM_Dtor        (ASM_t *ASM);

#endif //ASM_UTILS_H