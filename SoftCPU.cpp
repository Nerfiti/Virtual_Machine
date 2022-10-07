#include <assert.h>
#include <cstdio>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"
#include "stack.h"

const int version_CPU = 2;

struct SoftCPU
{
    Header head = {};
    int *code = nullptr;
    int IP = 0;
    stack_id main_stk = 0;
};


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

    SoftCPU CPU =
    {
        .head     = *data,
        .code     = (int *)(data + 1),
        .IP       = 0,
        .main_stk = 0
    };

    if (strcmp(CPU.head.signature, "PDA"))
    {
        printf("Wrong signature!");
        return -1;
    }
    if (CPU.head.version != version_CPU)
    {
        printf("Wrong program version!");
        return -1;
    }

    StackCtor(&(CPU.main_stk));

    int cmd_count = 0;
    while(cmd_count < CPU.head.numbers_of_the_commands)
    {
        cmd_count++;
        int a = 0,
            b = 0;
        
        switch(CPU.code[CPU.IP])
        {
            case CMD_PUSH:
            {
                StackPush(CPU.main_stk, CPU.code[CPU.IP + 1]);
                CPU.IP += 2;
                break;
            }
            case CMD_ADD:
            {
                StackPop(CPU.main_stk, &a);
                StackPop(CPU.main_stk, &b);
                StackPush(CPU.main_stk, a + b);
                CPU.IP++;
                break;
            }
            case CMD_SUB:
            {
                StackPop(CPU.main_stk, &a);
                StackPop(CPU.main_stk, &b);
                StackPush(CPU.main_stk, b - a);
                CPU.IP++;
                break;
            }
            case CMD_MUL:
            {
                StackPop(CPU.main_stk, &a);
                StackPop(CPU.main_stk, &b);
                StackPush(CPU.main_stk, a * b);
                CPU.IP++;
                break;
            }
            case CMD_DIV:
            {
                StackPop(CPU.main_stk, &a);
                StackPop(CPU.main_stk, &b);
                assert(a != 0);
                StackPush(CPU.main_stk, b / a);
                CPU.IP++;
                break;
            }
            case CMD_DUP:
            {
                StackPop (CPU.main_stk, &a);
                StackPush(CPU.main_stk,  a);
                StackPush(CPU.main_stk,  a);
                CPU.IP++;
                break;
            }
            case CMD_OUT:
            {
                StackPop(CPU.main_stk, &a);
                printf("Value: %d", a);
                fprintf(result, "Result = %d", a);
                CPU.IP++;
                break;
            }
            case CMD_HLT:
            {
                assert(!fclose(result));
                return 0;
            }
            default:
            {
                printf("Error. Non-existent command: %d\n", CPU.code[CPU.IP]);
                assert(!fclose(result));
                return 1;
            }
        }
    }
    
    assert(!fclose(result));
    return 0;
}
