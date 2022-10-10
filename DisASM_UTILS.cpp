#include "DisASM_UTILS.h"

const int   version_CPU     = 2;
const char *input_filename  = "./Code_machine.bin";
const char *output_filename = "./DisASM Result.txt";

void init_ASM(DisASM *disasm)
{
    assert(disasm);

    FILE *code_bin    = fopen(input_filename, "rb");
    assert(code_bin);

    size_t file_size  = get_file_size(code_bin);

    Header *data      = (Header *)calloc(file_size, 1);
    assert(data);

    fread(data, file_size, 1, code_bin);
    assert(!fclose(code_bin));

    disasm->head     = data;
    disasm->code     = (int *)(data + 1);
    disasm->IP       = 0;

    if (strcmp(disasm->head->signature, "PDA"))
    {
        printf("Wrong signature!");
        abort;
    }
    if (disasm->head->version != version_CPU)
    {
        printf("Wrong program version!");
        abort;
    }
}

void execute_ASM(DisASM *disasm)
{
    FILE *DisASM_result = fopen(output_filename, "w");
    
    fprintf(DisASM_result, "%s %d\n", disasm->head->signature, disasm->head->version);

    while(true)
    {
        int a = 0,
            b = 0;
        
       switch(disasm->code[disasm->IP])
        {
            case CMD_PUSH:
            {
                fprintf(DisASM_result, "PUSH %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_ADD:
            {
                fprintf(DisASM_result, "ADD\n");
                disasm->IP++;
                break;
            }
            case CMD_SUB:
            {
                fprintf(DisASM_result, "SUB\n");
                disasm->IP++;
                break;
            }
            case CMD_MUL:
            {
                fprintf(DisASM_result, "MUL\n");
                disasm->IP++;
                break;
            }
            case CMD_DIV:
            {
                fprintf(DisASM_result, "DIV\n");
                disasm->IP++;
                break;
            }
            case CMD_DUP:
            {
                fprintf(DisASM_result, "DUP\n");
                disasm->IP++;
                break;
            }
            case CMD_OUT:
            {
                fprintf(DisASM_result, "OUT\n");
                disasm->IP++;
                break;
            }
            case CMD_HLT:
            {
                fprintf(DisASM_result, "HLT\n");
                assert(!fclose(DisASM_result));
                return;
            }
            default:
            {
                fprintf(DisASM_result, "Error. Non-existent command: %d\n", disasm->code[disasm->IP]);
                assert(!fclose(DisASM_result));
                return;
            }
        }
    }
}