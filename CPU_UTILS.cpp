#include "CPU_UTILS.h"

const int   version_CPU     = 2;
const char *input_filename  = "./Code_machine.bin";
const char *output_filename = "./Result.txt";

void init_CPU(SoftCPU *CPU)
{
    assert(CPU);

    FILE *code_bin    = fopen(input_filename, "rb");
    assert(code_bin);

    size_t file_size  = get_file_size(code_bin);

    Header *data      = (Header *)calloc(file_size, 1);
    assert(data);

    fread(data, file_size, 1, code_bin);
    assert(!fclose(code_bin));

    StackCtor(&(CPU->main_stk));
    CPU->head     = data;
    CPU->code     = (int *)(data + 1);
    CPU->IP       = 0;
    CPU->result   = fopen(output_filename, "w");
    assert(CPU->result);

    if (strcmp(CPU->head->signature, "PDA"))
    {
        printf("Wrong signature!");
        abort;
    }
    if (CPU->head->version != version_CPU)
    {
        printf("Wrong program version!");
        abort;
    }
}

void execute_CPU(SoftCPU *CPU)
{
    while(true)
    {
        int a = 0,
            b = 0;
        
        switch(CPU->code[CPU->IP])
        {
            case CMD_PUSH:
            {
                StackPush(CPU->main_stk, CPU->code[CPU->IP + 1]);
                CPU->IP += 2;
                break;
            }
            case CMD_ADD:
            {
                StackPop (CPU->main_stk, &a);
                StackPop (CPU->main_stk, &b);
                StackPush(CPU->main_stk, a + b);
                CPU->IP++;
                break;
            }
            case CMD_SUB:
            {
                StackPop (CPU->main_stk, &a);
                StackPop (CPU->main_stk, &b);
                StackPush(CPU->main_stk, b - a);
                CPU->IP++;
                break;
            }
            case CMD_MUL:
            {
                StackPop (CPU->main_stk, &a);
                StackPop (CPU->main_stk, &b);
                StackPush(CPU->main_stk, a * b);
                CPU->IP++;
                break;
            }
            case CMD_DIV:
            {
                StackPop(CPU->main_stk, &a);
                StackPop(CPU->main_stk, &b);
                assert(a != 0);
                StackPush(CPU->main_stk, b / a);
                CPU->IP++;
                break;
            }
            case CMD_DUP:
            {
                StackPop (CPU->main_stk, &a);
                StackPush(CPU->main_stk,  a);
                StackPush(CPU->main_stk,  a);
                CPU->IP++;
                break;
            }
            case CMD_OUT:
            {
                StackPop(CPU->main_stk, &a);
                printf("Value: %d", a);
                fprintf(CPU->result, "Result = %d", a);
                CPU->IP++;
                break;
            }
            case CMD_HLT:
            {
                assert(!fclose(CPU->result));
                return;
            }
            default:
            {
                printf("Error. Non-existent command: %d\n", CPU->code[CPU->IP]);
                assert(!fclose(CPU->result));
                return;
            }
        }
    }
}