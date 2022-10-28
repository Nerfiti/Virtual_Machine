#include "CPU_UTILS.h"

#define STACK        CPU->main_stk
#define POP(val)     StackPop(STACK, val)
#define PUSH(val)    StackPush(STACK, val)
#define IP           CPU->IP
#define CODE         CPU->code
#define CMD          CODE[IP]
#define ARG(n)       CODE[IP + n]//
#define REG(n)       CPU->reg[n]
#define RAM(n)       CPU->ram[n]
#define RETSTACK     CPU->ret_stk
#define RETPUSH(val) StackPush(RETSTACK, val)
#define RETPOP(val)  StackPop(RETSTACK, val)  

void init_CPU(SoftCPU *CPU)
{
    assert(CPU);
    const int start_video_memory = 300;
    const char *input_filename   = "./Generals/code_machine.bin";
    const char *output_filename  = "./CPU/Result.txt";

    FILE *code_bin = fopen(input_filename, "rb");
    assert(code_bin);

    size_t file_size = get_file_size(code_bin);

    Header *data = (Header *)calloc(file_size, 1);
    assert(data);

    fread(data, file_size, 1, code_bin);
    assert(!fclose(code_bin));

    StackCtor(&(STACK   ));
    StackCtor(&(RETSTACK));
    CPU->head   = data;
    CODE        = (int *)(data + 1);
    IP          = 0;
    CPU->result = fopen(output_filename, "w");
    REG(0)      = start_video_memory;
    assert(CPU->result);

    CheckHead(*CPU->head);
} 

void execute_CPU(SoftCPU *CPU)
{       
    const int window_width  = 150;
    const int window_height = 40;    

    #define DEF_CMD(cmd, num, code) \
        case num:                   \
        {                           \
            code                    \
            DUMP_ON(Dump(CPU));     \
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
    const int version_CPU = 6;
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

void Dump(SoftCPU *CPU)
{
    IP++;
    StackDump(STACK);
    int start = (0 > IP - 4) ? 0 : IP - 4;
    int finish = 0;
    for (int i = 0; i <= 4; ++i)
    {
        finish = IP + i;
        if (CODE[IP + i] == CMD_HLT) break;
    }
    printf("IP   --| ");
    for (int i = start; i < finish; ++i)
    {
        printf(" %3d ", i);
    }
    printf(" |--\n" "CODE --| ");
    for (int i = start; i < finish; ++i)
    {
        printf(" %3d ", CODE[i] & cmd_id_mask);
    }
    printf(" |--\n      ");
    for (int i = start; i < IP; ++i)
    {
        printf("     ");
    }
    printf("^\n      ");
    for (int i = start; i < IP; ++i)
    {
        printf("     ");
    }
    printf("| Instruction Pointer (IP)\n");
    system("pause");
    IP--;
}

void Paint(int max_symbols, int window_width, int window_height, int *video_memory)
{
    if (max_symbols <= 0)
    {
        max_symbols = window_width*window_height;
    }

    char screen[window_width*window_height + 1] = "";
    bool break_flag = false;
    
    for (int y = 0; y < window_height; ++y)
    {
        if (break_flag)
        {
            break;
        }

        for (int x = 0; x < window_width; ++x)
        {
            int point = x + window_width * y;
            if (point > max_symbols)
            {
                break_flag = true;
                break;
            }

            screen[point] = video_memory[point];
        }
        screen[(y+1)*window_width - 1] = '\n';
    }
    printf("%s", screen);
}

int *ProcArgsPushAndPop(int command, SoftCPU *CPU, int *args, bool pop)
{
    if ((command & With_RAM) && (command & With_REG) && (command & With_PLUS))
    {
        IP++;
        if (args[0] + REG(args[1]) < 0 || args[0] + REG(args[1]) > size_of_ram) SegFault();
        return &RAM(args[0] + REG(args[1]));
    }
    if ((command & With_RAM) && (command & With_REG)) return &RAM(REG(args[0]));
    if ( command & With_RAM)                          return &RAM(args[0]);
    if ( command & With_REG)                          return &REG(args[0]);
    if (pop) SegFault();
    return args;
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