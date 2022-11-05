#include "ASM_UTILS.h"

void init_ASM(ASM_t *ASM)
{
    const char *input_filename = "./ASM/input.txt";

    FILE *input_file  = fopen(input_filename, "r");
    assert(input_file);
    
    file_to_memory(input_file, &ASM->input_data);
    text_to_lines (&ASM->input_data);

    ASM->code = (int *)calloc(3 * ASM->input_data.nLines, sizeof(int));
    assert(ASM->code);

    assert(!fclose(input_file));
}

int execute_ASM(ASM_t *ASM, bool first_assemble)
{
    const char *listing_filename = "./ASM/Listing.txt";

    FILE *listing_file = fopen(listing_filename, "w");
    
    assert(listing_file);

    int *code    = ASM->code;
    int line     = 0;
    int position = 0;
    ASM->index   = 0;
    ASM->ip      = 0;
    Text *input_data = &ASM->input_data;

    char command[maximum_cmd_length + 1] = "";  
    
    PrintHeader(listing_file);

    while(line < input_data->nLines)
    {
        DelComment(input_data->lines[line].start, ';');

        char arg[maximum_cmd_length] = "";
        char *string = input_data->lines[line].start;
        sscanf(string, "%s%n %s", command, &position, arg);

        #define DEF_CMD(cmd, num, ...)                                                                          \
            if (stricmp(command, cmds[num]) == 0)                                                               \
            {                                                                                                   \
                int argc = 0;                                                                                   \
                int mode = ProcArgsGetMode(*ASM, string + position, code + ASM->ip + 1, &argc, first_assemble); \
                code[ASM->ip] = CMD_##cmd | mode;                                                               \
                                                                                                                \
                PrintListing(listing_file, string, code + ASM->ip, argc + 1);                                   \
                                                                                                                \
                ASM->ip += argc + 1;                                                                            \
            }                                                                                                   \
            else                                                                               

        #include "cmds.h"
        //else
        {
            if (strchr(command, ':'))
            {
                SetLabel(ASM, command, ASM->ip);
            }
            else if (stricmp(command, ";") == 0)
            {
                ;
            }
            else if (strchr(input_data->lines[line].start, '='))
            {
                int value =  0;

                sscanf(input_data->lines[line].start, "%*[^=]= %d", &value);
                SetLabel(ASM, command, value);
            }
            else 
            {
                printf("Syntax Error: non-existent command: %s", command);
                return -1;
            }
        }

        #undef DEF_CMD

        line++;
    }
    
    assert(!fclose(listing_file));
    return 0;
}

void optimizeExecute(ASM_t *ASM) //-O9
{
    int *code = ASM->code;
    int  argc = 0;

    for (int ip = 0; ip < 3*ASM->input_data.nLines*sizeof(int); ip += argc + 1)
    {
        if (code[ip] == CMD_PUSH || code[ip] == CMD_POP)
        {
            argc = 1;
            if (code[ip] & With_PLUS)
            {
                argc = 2;
            }
        }
        else if (code[ip] == CMD_CALL || code[ip] == CMD_PNT || code[ip] == CMD_SLP || code[ip] == CMD_COLOR)
        {
            argc = 1;
        }
        else if (code[ip] == CMD_JB   || code[ip] == CMD_JBE || code[ip] == CMD_JA ||
                 code[ip] == CMD_JAE  || code[ip] == CMD_JE  || code[ip] == CMD_JNE)
        {
            if (code[ip + 1] == ip + 2   && ip > 3 && 
                code[ip - 2] == CMD_PUSH && code[ip - 4] == CMD_PUSH)
            {
                argc = 1;
                for (int i = ip - 4; i <= ip + 1; ++i)
                {
                    code[i] = CMD_NOP;
                }
            }
        }   
        else if (code[ip] == CMD_JMP)
        {
            argc = 1;

            if(code[ip + 1] == ip + 2)
            {
                code[ip]     = CMD_NOP;
                code[ip + 1] = CMD_NOP;
            }
        }
        else
        {
            argc = 0;
        }
    }
}

int  SearchName(ASM_t ASM, char *name)
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

int  ProcArgsGetMode(ASM_t ASM, char *args_line, int *args, int *argc, bool first_assemble)
{
    if (strchr(args_line, ':') && first_assemble)
    {
        *argc = 1;
        return 0;
    }

    int address_num = 0;
    char name[maximum_cmd_length] = "";

    sscanf(args_line, "%s", name);
    address_num = SearchName(ASM, name);
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
                if ((args[1] = GetRegNum(sarg)) == -1 && !first_assemble)
                {
                    printf("Syntax Error: Wrong Register Name. %s\n", sarg);
                    abort();
                }
            }

            if (*sarg != 'R')
            {
                args[0] = atoi(sarg);
                if ((args[1] = GetRegNum(farg)) == -1 && !first_assemble)
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
            if ((args[0] = GetRegNum(arg)) == -1 && !first_assemble)
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
        
        if ((args[0] = GetRegNum(reg_start)) == -1 && !first_assemble)
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
    fprintf(listing_file, "%-20s | %d ", asm_line, code[0] & cmd_id_mask);
    
    for (int i = 1; i < argc; ++i)
    {
        fprintf(listing_file, "%d ", code[i]);
    }
    fprintf(listing_file, "\n");
}

void PrintHeader(FILE* listing_file)
{
    Header head = {};
    fprintf(listing_file, "%s %d\n", head.signature, head.version);
}

void DelComment(char *line, char comm_symbol)
{
    if (char *comment = strchr(line, comm_symbol))
    {
        comment[1] = '\0';
    }
}

void SetLabel(ASM_t *ASM, char *command, int value)
{
    int name_num = 0;
    if ((name_num = SearchName(*ASM, command)) != -1)
    {
        ASM->label_arr[name_num].value = value;
    }
    else
    {
        sscanf(command, "%s:", ASM->label_arr[ASM->index].name);
        ASM->label_arr[ASM->index].value = value;
        ASM->index++;
    }
}

void PrintCode(int *code, int code_len)
{
    const char *out_bin_filename = "./Generals/code_machine.bin";
    FILE *out_bin = fopen(out_bin_filename, "wb");
    assert(out_bin);

    Header head = {};

    fwrite(&head, sizeof(char), sizeof(Header), out_bin);
    fwrite(code , sizeof(char), code_len * sizeof(int), out_bin);

    assert(!fclose(out_bin));
}

int  GetRegNum(char *reg_name)
{
    const int reg_len = 3;
    if (strnicmp(reg_name, "RAX", reg_len) == 0)
    {
        return RAX;
    }
    if (strnicmp(reg_name, "RBX", reg_len) == 0)
    {
        return RBX;
    }
    if (strnicmp(reg_name, "RCX", reg_len) == 0)
    {
        return RCX;
    }
    if (strnicmp(reg_name, "RDX", reg_len) == 0)
    {
        return RDX;
    } 
    return Wrong_Reg;
}

void ASM_Dtor(ASM_t *ASM)
{
    free(ASM->code);
    ASM->index = -1;
}

ProgMode getProgramMode(const int argc, const char *argv[])
{
    ProgMode mode = 0;
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-O9") == 0)
        {
            mode |= O9;
        }
        else
        {
            mode |= WrongMode;
        }
    }
    return mode;
}