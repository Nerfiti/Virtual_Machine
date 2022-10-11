#include "ASM_UTILS.h"

const Header head = {};

const char *input_filename    = "Input.txt";
const char *listing_filename  = "Listing.txt";
const char *out_bin_filename  = "code_machine.bin";
const int   label_arr_size    = 100;

label l_arr[label_arr_size]   = {};

ASM_t ASM = 
{
    .label_arr = l_arr,
    .index = 0
};

void init_ASM(Text *input_data)
{
    FILE *input_file  = fopen("Input.txt", "r");
    assert(input_file );

    file_to_memory(input_file, input_data);
    text_to_lines (input_data);
}


void execute_ASM(Text input_data, bool first_assemble)
{
    FILE *listing_file = fopen(listing_filename, "w");
    FILE *out_bin      = fopen(out_bin_filename, "wb");
    
    assert(listing_file);
    assert(out_bin     );

    int *code    = (int *)calloc(2 * input_data.nLines, sizeof(int));
    int line     = 0;
    int position = 0;
    int IP       = 0;
    ASM.index    = 0;

    char cmd[maximum_cmd_length + 1] = "";  
    assert(code);
    
    fprintf(listing_file, "%s %d\n", head.signature, head.version);

    while(line < input_data.nLines)
    {
        if (char *comment = strchr(input_data.lines[line].start, ';'))
        {
            comment[1] = '\0';
        }
        
        sscanf(input_data.lines[line].start, "%s%n", cmd, &position);

        if (stricmp(cmd, cmds[CMD_PUSH]) == 0)
        {
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start + position, "%s", arg);
            if (stricmp(arg, "RAX") == 0)
            {
                code[IP] = CMD_PUSH | 1<<5;
                code[IP + 1] = RAX;
                IP += 2;
                fprintf(listing_file, "%s %-11s | %d %-11d\n", cmds[CMD_PUSH], "RAX", CMD_PUSH, RAX);
            }
            else if (stricmp(arg, "RBX") == 0)
            {
                code[IP] = CMD_PUSH | 1<<5;
                code[IP + 1] = RBX;
                IP += 2;
                fprintf(listing_file, "%s %-11s | %d %-11d\n", cmds[CMD_PUSH], "RBX", CMD_PUSH, RBX);
            }
            else if (stricmp(arg, "RCX") == 0)
            {
                code[IP] = CMD_PUSH | 1<<5;
                code[IP + 1] = RCX;
                IP += 2;
                fprintf(listing_file, "%s %-11s | %d %-11d\n", cmds[CMD_PUSH], "RCX", CMD_PUSH, RCX);
            }
            else if (stricmp(arg, "RDX") == 0)
            {
                code[IP] = CMD_PUSH | 1<<5;
                code[IP + 1] = RDX;
                IP += 2;
                fprintf(listing_file, "%s %-11s | %d %-11d\n", cmds[CMD_PUSH], "RDX", CMD_PUSH, RDX);
            }
            else
            {
                code[IP] = CMD_PUSH;
                int value = 0;
                sscanf(input_data.lines[line].start + position, "%d", &value);
                fprintf(listing_file, "%s %-11d | %d %-11d\n", cmds[CMD_PUSH], value, CMD_PUSH, value);
                code[IP + 1] = value;
                IP += 2;
            }

        }
        else if (stricmp(cmd, cmds[CMD_ADD]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_ADD], CMD_ADD);

            code[IP] = CMD_ADD;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_SUB]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_SUB], CMD_SUB);

            code[IP] = CMD_SUB;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_MUL]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_MUL], CMD_MUL);

            code[IP] = CMD_MUL;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_DIV]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_DIV], CMD_DIV);

            code[IP] = CMD_DIV;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_DUP]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_DUP], CMD_DUP);

            code[IP] = CMD_DUP;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_OUT]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_OUT], CMD_OUT);

            code[IP] = CMD_OUT;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_JMP]) == 0)
        {
            code[IP] = CMD_JMP;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JMP], arg, CMD_JMP, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JB]) == 0)
        {
            code[IP] = CMD_JB;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JB], arg, CMD_JB, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JBE]) == 0)
        {
            code[IP] = CMD_JBE;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JBE], arg, CMD_JBE, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JA]) == 0)
        {
            code[IP] = CMD_JA;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JA], arg, CMD_JA, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JAE]) == 0)
        {
            code[IP] = CMD_JAE;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JAE], arg, CMD_JAE, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JE]) == 0)
        {
            code[IP] = CMD_JE;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JE], arg, CMD_JE, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_JNE]) == 0)
        {
            code[IP] = CMD_JNE;
            char arg[maximum_cmd_length] = "";
            sscanf(input_data.lines[line].start, "%*s %s", arg);
            if ((position = SearchName(arg)) == -1 && !first_assemble)
            {
                printf("Syntax Error!");
                abort();
            }
            code[IP + 1] = ASM.label_arr[position].value;
            IP += 2;

            fprintf(listing_file, "%-3s %-12s | %d %d\n", cmds[CMD_JNE], arg, CMD_JNE, code[IP - 1]);
        }
        else if (stricmp(cmd, cmds[CMD_HLT]) == 0)
        {
            fprintf(listing_file, "%-16s | %d\n", cmds[CMD_HLT], CMD_HLT);

            code[IP] = CMD_HLT;
            IP++;
            break;
        }
        else
        {
            if (strchr(cmd, ':'))
            {
                int name_num = 0;
                if ((name_num = SearchName(cmd)) != -1)
                {
                    ASM.label_arr[name_num].value = IP;
                }
                else
                {
                    sscanf(cmd, "%s:", ASM.label_arr[ASM.index].name);
                    ASM.label_arr[ASM.index].value = IP;
                    ASM.index++;
                }
            }
        }
        line++;
    }

    fwrite(&head, sizeof(char), sizeof(Header)  , out_bin);
    fwrite(code , sizeof(char), IP * sizeof(int), out_bin);

    assert(!fclose(listing_file));
    assert(!fclose(out_bin    ));
}

int SearchName(char *name)
{
    for (int i = 0; i < label_arr_size; ++i)
    {
        if (stricmp(name, ASM.label_arr[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}