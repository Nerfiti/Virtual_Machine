#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"

const int version_CPU = 1;

int main()
{  
    FILE *code_bin    = fopen("code_machine.bin", "rb");
    assert(code_bin);

    size_t file_size  = get_file_size(code_bin);
    Header *data      = (Header *)calloc(file_size, 1);
    
    fread(data, file_size, 1, code_bin);
    assert(!fclose(code_bin));

    if (strcmp(data->signature, "PDA"))
    {
        printf("Wrong signature!");
        return -1;
    }
    if (data->version != version_CPU)
    {
        printf("Wrong program version!");
        return -1;
    }

    int cmd_count         = 0;
    int number_of_cmds    = data->numbers_of_the_commands;
    int IP                = 0;
    int *code             = (int *)(data + 1);

    FILE   *DisASM_result = fopen("DisASM Result.txt", "w");
    fprintf(DisASM_result, "%s %d %d\n", data->signature, data->version, data->numbers_of_the_commands);

    while(cmd_count < number_of_cmds)
    {
        cmd_count++;
        int a = 0,
            b = 0;
        
        switch(code[IP])
        {
            case CMD_PUSH:
            {
                fprintf(DisASM_result, "PUSH %d\n", code[IP + 1]);
                IP += 2;
                break;
            }
            case CMD_ADD:
            {
                fprintf(DisASM_result, "ADD\n");
                IP++;
                break;
            }
            case CMD_SUB:
            {
                fprintf(DisASM_result, "SUB\n");
                IP++;
                break;
            }
            case CMD_MUL:
            {
                fprintf(DisASM_result, "MUL\n");
                IP++;
                break;
            }
            case CMD_DIV:
            {
                fprintf(DisASM_result, "DIV\n");
                IP++;
                break;
            }
            case CMD_OUT:
            {
                fprintf(DisASM_result, "OUT\n");
                IP++;
                break;
            }
            case CMD_HLT:
            {
                fprintf(DisASM_result, "HLT\n");
                break;
            }
            default:
            {
                fprintf(DisASM_result, "Error. Non-existent command: %d\n", code[IP]);
            }
        }
    }
    assert(!fclose(DisASM_result));

    return 0;
}