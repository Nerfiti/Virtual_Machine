#include "ASM_UTILS.h"

const Header head = {};

ASM_t ASM = {};

void init_ASM(ASM_t *ASM)
{
    const char *input_filename = "C:/Users/penko/Projects/Compiler/ASM/input.txt";

    FILE *input_file  = fopen(input_filename, "r");
    assert(input_file);
    
    file_to_memory(input_file, &ASM->input_data);
    text_to_lines (&ASM->input_data);

    assert(!fclose(input_file));
}


void execute_ASM(ASM_t *ASM, bool first_assemble)
{
    const char *listing_filename  = "C:/Users/penko/Projects/Compiler/ASM/Listing.txt";
    const char *out_bin_filename  = "C:/Users/penko/Projects/Compiler/Generals/code_machine.bin";

    FILE *listing_file = fopen(listing_filename, "w");
    FILE *out_bin      = fopen(out_bin_filename, "wb");
    
    assert(listing_file);
    assert(out_bin     );

    int *code    = (int *)calloc(2 * ASM->input_data.nLines, sizeof(int));
    assert(code);

    int line     = 0;
    int position = 0;
    int IP       = 0;
    ASM->index   = 0;
    Text *input_data = &ASM->input_data;

    char command[maximum_cmd_length + 1] = "";  
    
    PrintHeader(listing_file, head);

    while(line < input_data->nLines)
    {
        DelComment(input_data->lines[line].start, ';');

        char arg[maximum_cmd_length] = "";
        char *string = input_data->lines[line].start;
        sscanf(string, "%s%n %s", command, &position, arg);

        #define DEF_CMD(cmd, num, ...)                                                      \
            if (stricmp(command, cmds[num]) == 0)                                           \
            {                                                                               \
                int argc = 0;                                                               \
                int mode = 0;                                                               \
                if (!first_assemble)                                                        \
                {                                                                           \
                    mode = ProcArgsGetMode(string + position, code + IP + 1, &argc);        \
                }                                                                           \
                code[IP] = CMD_##cmd | mode;                                                \
                                                                                            \
                PrintListing(listing_file, string, code + IP, argc + 1);                    \
                                                                                            \
                IP += argc + 1;                                                             \
            }                                                                               \
            else                                                                               

        #include "cmds.h"
        //else
        {
            if (strchr(command, ':'))
            {
                SetLabel(command, IP);
            }
            else if (stricmp(command, ";") == 0)
            {
                ;
            }
            else if (strchr(input_data->lines[line].start, '='))
            {
                int value =  0;

                sscanf(input_data->lines[line].start, "%*[^=]= %d", &value);
                SetLabel(command, value);
            }
            else 
            {
                printf("Syntax Error: non-existent command: %s", command);
                abort();
            }
        }

        #undef DEF_CMD

        line++;
    }
    
    PrintCode(out_bin, head, code, IP);

    assert(!fclose(listing_file));
    assert(!fclose(out_bin    ));
}

int SearchName(char *name)
{
    for (int i = 0; i < label_arr_size; ++i)
    {
        if (stricmp(name, ASM.label_arr[i].name) == 0 && *name != '\0')
        {
            return i;
        }
    }
    return -1;
}

int ProcArgsGetMode(char *args_line, int *args, int *argc)
{
    int address_num = 0;
    char name[maximum_cmd_length] = "";

    sscanf(args_line, "%s", name);
    address_num = SearchName(name);
    if (address_num != -1)
    {
        *argc = 1;
        *args = ASM.label_arr[address_num].value;
        return Without_special_args;
    }

    int   regnum    = -1;
    int   ramnum    = -1;
    char *reg_start = nullptr;
    char *ram_start = nullptr;

    if (ram_start = strchr(args_line, '['))
    {
        if (strchr(ram_start, '+'))
        {
            const int max_arg_len  = 50;
            char farg[max_arg_len] = "",
                 sarg[max_arg_len] = "";

            sscanf(ram_start, "[%[^+] + %[^]]", farg, sarg);

            if (*farg != 'R')
            {
                args[0] = atoi(farg);
                if ((args[1] = GetRegNum(sarg)) == -1)
                {
                    printf("Syntax Error: Wrong Register Name. %s\n", sarg);
                    abort();
                }
            }

            if (*sarg != 'R')
            {
                args[0] = atoi(sarg);
                if ((args[1] = GetRegNum(farg)) == -1)
                {
                    printf("Syntax Error: Wrong Register Name. %s\n", farg);
                    abort();
                }
            }
            *argc = 2;
            return With_REG | With_RAM | With_PLUS;
        }
        else
        {
            const int max_arg_len  = 50;
            char arg[max_arg_len]  = "";

            sscanf(ram_start, "[%[^]]", arg);

            if (*arg != 'R')
            {
                args[0] = atoi(arg);
                *argc = 1;
                return With_RAM;
            }
            
            //else
            if ((args[0] = GetRegNum(arg)) == -1)
            {
                printf("Syntax Error: Wrong Register Name. %s\n", arg);
                abort();
            }
            *argc = 1;
            return With_REG | With_RAM;
        }
    }
    else if (reg_start = strchr(args_line, 'R'))
    {
        *argc = 1;
        
        if ((args[0] = GetRegNum(reg_start)) == -1)
        {
            printf("Syntax Error: Wrong Register Name. %s\n", reg_start);
            abort();
        }

        return With_REG;
    }

    *argc = sscanf(args_line, "%d", args);
    if (*argc == EOF)
    {
        *argc = 0;
    }
    return Without_special_args;
}

void PrintListing(FILE* listing_file, char *asm_line, int *code, int argc)
{
    fprintf(listing_file, "%-20s |", asm_line);
    
    for (int i = 0; i < argc; ++i)
    {
        fprintf(listing_file, "%d ", code[i] & cmd_id_mask);
    }
    fprintf(listing_file, "\n");
}

void PrintHeader(FILE* listing_file, Header head)
{
    fprintf(listing_file, "%s %d\n", head.signature, head.version);
}

void DelComment(char *line, char comm_symbol)
{
    if (char *comment = strchr(line, comm_symbol))
    {
        comment[1] = '\0';
    }
}

void SetLabel(char *command, int value)
{
    int name_num = 0;
    if ((name_num = SearchName(command)) != -1)
    {
        ASM.label_arr[name_num].value = value;
    }
    else
    {
        sscanf(command, "%s:", ASM.label_arr[ASM.index].name);
        ASM.label_arr[ASM.index].value = value;
        ASM.index++;
    }
}

void PrintCode(FILE *out_bin, Header head, int *code, int code_len)
{
    fwrite(&head, sizeof(char), sizeof(Header)  , out_bin);
    fwrite(code , sizeof(char), code_len * sizeof(int), out_bin);
}

int GetRegNum(char *reg_name)
{
    if (strnicmp(reg_name, "RAX", 3) == 0)
    {
        return RAX;
    }
    if (strnicmp(reg_name, "RBX", 3) == 0)
    {
        return RBX;
    }
    if (strnicmp(reg_name, "RCX", 3) == 0)
    {
        return RCX;
    }
    if (strnicmp(reg_name, "RDX", 3) == 0)
    {
        return RDX;
    }
    return Wrong_Reg;
}