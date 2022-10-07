#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"
#include "stack.h"

const int version_CPU = 1;

int main()
{  
    FILE *code_bin    = fopen("./Code_machine.bin", "rb");
    FILE *result      = fopen("Result.txt", "w");
    
    assert(code_bin);
    assert(result);

    size_t file_size  = get_file_size(code_bin);
    Header *data      = (Header *)calloc(file_size, 1);
    assert(data);

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

    int cmd_count      = 0;
    int number_of_cmds = data->numbers_of_the_commands;
    int IP             = 0;
    int *code          = (int *)(data + 1);
    stack_id main_stk  = 0;
    
    StackCtor(&main_stk, 4);

    while(cmd_count < number_of_cmds)
    {
        cmd_count++;
        int a = 0,
            b = 0;

        switch(code[IP])
        {
            case CMD_PUSH:
            {
                StackPush(main_stk, code[IP + 1]);
                IP += 2;
                break;
            }
            case CMD_ADD:
            {
                StackPop(main_stk, &a);
                StackPop(main_stk, &b);
                StackPush(main_stk, a + b);
                IP++;
                break;
            }
            case CMD_SUB:
            {
                StackPop(main_stk, &a);
                StackPop(main_stk, &b);
                StackPush(main_stk, b - a);
                IP++;
                break;
            }
            case CMD_MUL:
            {
                StackPop(main_stk, &a);
                StackPop(main_stk, &b);
                StackPush(main_stk, a * b);
                IP++;
                break;
            }
            case CMD_DIV:
            {
                StackPop(main_stk, &a);
                StackPop(main_stk, &b);
                assert(b != 0);
                StackPush(main_stk, b / a);
                IP++;
                break;
            }
            case CMD_OUT:
            {
                StackPop(main_stk, &a);

                printf("Value: %d", a);
                fprintf(result, "Result = %d", a);

                IP++;
                break;
            }
            case CMD_HLT:
            {
                assert(!fclose(result));
                return 0;
            }
            default:
            {
                printf("Error. Non-existent command: %d\n", code[IP]);
                assert(!fclose(result));
                return 1;
            }
        }
    }
    
    assert(!fclose(result));
    return 0;
}
