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
};

enum Regs
{
    Wrong_Reg = -1,
    RAX       =  1,
    RBX       =  2,
    RCX       =  3,
    RDX       =  4
};


int  ProcArgsGetMode (ASM_t ASM, char *args_line, int *args, int *argc, bool first_assemble);
void init_ASM        (ASM_t *ASM);
void execute_ASM     (ASM_t *ASM, bool first_assemble);
int  SearchName      (ASM_t ASM, char *name);
void PrintListing    (FILE *listingfile, char *asm_line, int *code, int argc);
void PrintHeader     (FILE* listing_file, Header head);
void DelComment      (char *line, char comm_symbol);
void SetLabel        (ASM_t *ASM, char *command, int value);
void PrintCode       (FILE *out_bin, Header head, int *code, int code_len);
int  GetRegNum       (char *reg_name);

#endif //ASM_UTILS_H