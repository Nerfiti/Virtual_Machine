#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "Comp_Generals.h"
#include "linesLib.h"
    
const int version_ASM = 1;

int main()
{
    FILE *input_file  = fopen("Input.txt", "r");
    FILE *output_file = fopen("Listing.txt", "w");
    FILE *out_bin     = fopen("code_machine.bin", "wb");
    Text input_data   = {};
    
    assert(input_file );
    assert(output_file);
    assert(out_bin    );

    file_to_memory(input_file, &input_data);
    text_to_lines (&input_data);

    int *code                        = (int *)calloc(2 * input_data.nLines, sizeof(int));
    int line                         = 0;
    int position                     = 0;
    int IP                           = 0;
    char cmd[maximum_cmd_length + 1] = "";  

    Header head = 
    {
        .signature                   = "PDA",
        .version                     = version_ASM,
        .numbers_of_the_commands     = input_data.nLines
    };

    assert(code);
    
    fprintf(output_file, "%s %d %d\n", head.signature, head.version, head.numbers_of_the_commands);

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

            fprintf(output_file, "%s %-11d | %d %-11d\n", cmds[CMD_PUSH], value, CMD_PUSH, value);

            code[IP] = CMD_PUSH;
            code[IP + 1] = value;
            IP += 2;
        }
        else if (stricmp(cmd, cmds[CMD_ADD]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_ADD], CMD_ADD);

            code[IP] = CMD_ADD;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_SUB]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_SUB], CMD_SUB);

            code[IP] = CMD_SUB;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_MUL]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_MUL], CMD_MUL);

            code[IP] = CMD_MUL;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_DIV]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_DIV], CMD_DIV);

            code[IP] = CMD_DIV;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_OUT]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_OUT], CMD_OUT);

            code[IP] = CMD_OUT;
            IP++;
        }
        else if (stricmp(cmd, cmds[CMD_HLT]) == 0)
        {
            fprintf(output_file, "%-16s | %d\n", cmds[CMD_PUSH], CMD_HLT);

            code[IP] = CMD_HLT;
            IP++;
        }
        line++;
    }

    fwrite(&head, sizeof(char), sizeof(Header)  , out_bin);
    fwrite(code , sizeof(char), IP * sizeof(int), out_bin);

    assert(!fclose(input_file ));
    assert(!fclose(output_file));
    assert(!fclose(out_bin    ));

    return 0;
}
