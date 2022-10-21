#include "CPU_UTILS.h"

const int   version_CPU        = 6;
const int   start_video_memory = 300;
const int   window_width       = 150;
const int   window_height      = 40;
const char *input_filename     = "C:/Users/penko/Projects/Compiler/Generals/code_machine.bin";
const char *output_filename    = "C:/Users/penko/Projects/Compiler/CPU/Result.txt";

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
    CPU->reg[0]   = start_video_memory;
    assert(CPU->result);

    CheckHead(*CPU->head);
}

void execute_CPU(SoftCPU *CPU)
{

    #define STACK        CPU->main_stk
    #define POP(val)     StackPop(STACK, val)
    #define PUSH(val)    StackPush(STACK, val)
    #define IP           CPU->IP
    #define CODE         CPU->code
    #define CMD          CODE[IP]
    #define ARG(n)       CODE[IP + n]
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
    #undef STACK
    #undef POP
    #undef PUSH
    #undef IP
    #undef CODE
    #undef CMD
    #undef ARG
    #undef REG
    #undef RAM
    #undef RETSTACK
    #undef RETPUSH
    #undef RETPOP
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