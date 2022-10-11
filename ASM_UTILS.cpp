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


void execute_ASM(Text input_data)
{
    FILE *listing_file = fopen(listing_filename, "w");
    FILE *out_bin      = fopen(out_bin_filename, "wb");
    
    assert(listing_file);
    assert(out_bin     );

    int *code    = (int *)calloc(2 * input_data.nLines, sizeof(int));
    int line     = 0;
    int position = 0;
    int IP       = 0;

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
            int value = 0;
            sscanf(input_data.lines[line].start + position, "%d", &value);

            fprintf(listing_file, "%s %-11d | %d %-11d\n", cmds[CMD_PUSH], value, CMD_PUSH, value);

            code[IP] = CMD_PUSH;
            code[IP + 1] = value;
            IP += 2;
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
                printf("%s\n", cmd);
                int name_num = 0;
                if ((name_num = SearchName(cmd)) != -1)
                {
                    ASM.label_arr[name_num].value = IP + 1;
                    continue;
                }
                sscanf(cmd, "%s:", ASM.label_arr[ASM.index].name);
                ASM.label_arr[ASM.index].value = IP + 1;

                ASM.index++;
            }
        }
        line++;
    }

    fwrite(&head, sizeof(char), sizeof(Header)  , out_bin);
    fwrite(code , sizeof(char), IP * sizeof(int), out_bin);
    
    for (int i = 0; i < ASM.index; ++i)
    {
        fprintf(listing_file, "%s: %d\n", 
            ASM.label_arr[i].name, ASM.label_arr[i].value);
    }

    assert(!fclose(listing_file));
    assert(!fclose(out_bin    ));
}

int SearchName(char *name)
{
    for (int i = 0; i < ASM.index; ++i)
    {
        printf("i = %d\n", i);
        if (stricmp(name, ASM.label_arr[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}