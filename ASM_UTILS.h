#ifndef ASM_UTILS_H
#define ASM_UTILS_H

#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"

extern const Header head;
extern const char *input_filename;
extern const char *listing_filename;
extern const char *out_bin_filename;

struct label
{
    int value = 0;
    char name[maximum_cmd_length] = "";    
};

struct ASM_t
{
    label* label_arr = nullptr;
    int index = 0;
};



void init_ASM(Text *input_data);
void execute_ASM(Text input_data, bool first_assemble);
int SearchName(char *name);

#endif //ASM_UTILS_H