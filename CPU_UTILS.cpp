#include "CPU_UTILS.h"

const int   version_CPU         = 6;
const char *input_filename      = "./Code_machine.bin";
const char *output_filename     = "./Result.txt";

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
    StackCtor(&(CPU->ret_stk ));
    CPU->head     = data;
    CPU->code     = (int *)(data + 1);
    CPU->IP       = 0;
    CPU->result   = fopen(output_filename, "w");
    assert(CPU->result);

    CheckHead(*CPU->head);
}

void execute_CPU(SoftCPU *CPU)
{

    #define STACK        CPU->main_stk
    #define POP(val)     StackPop(STACK, val)
    #define PUSH(val)    StackPush(STACK, val)
    #define IP           CPU->IP
    #define CMD          CPU->code[IP]
    #define ARG(n)       CPU->code[IP + n]
    #define REG(n)       CPU->reg[n]
    #define RAM(n)       CPU->ram[n]
    #define RETSTACK     CPU->ret_stk
    #define RETPUSH(val) StackPush(RETSTACK, val)
    #define RETPOP(val)  StackPop(RETSTACK, val)   

    #define DEF_CMD(cmd, num, code) \
        case num:                   \
        {                           \
            code                    \
            break;                  \
        }                           \

    while(true)
    {
        int first_operand  = 0,
            second_operand = 0;
            
        switch(CMD & cmd_id_mask)
        {
            #include "cmds.h"
            default:
            {
                printf("Error. Non-existent command: %d\n", CMD);
                assert(!fclose(CPU->result));
                return;
            }
        }
    }
    #undef DEF_CMD
}

void CheckHead(Header head)
{
    if (strcmp(head.signature, "PDA"))
    {
        printf("Wrong signature!");
        abort();
    }
    if (head.version != version_CPU)
    {
        printf("Wrong program version!");
        abort();
    }
}

void SegFault()
{
    printf("\nSEGMENTATION FAULT\n");
    abort();
}