#include "DisASM_UTILS.h"

const int   version_CPU     = 4;
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
            case CMD_PUSH | 1<<5:
            {
                fprintf(DisASM_result, "PUSH ");
                switch (disasm->code[disasm->IP + 1])
                {
                case 1:
                {
                    fprintf(DisASM_result, "RAX\n");
                    break;
                } 
                case 2:
                {
                    fprintf(DisASM_result, "RBX\n");
                    break;
                }
                case 3:
                {
                    fprintf(DisASM_result, "RCX\n");
                    break;
                }
                case 4:
                {
                    fprintf(DisASM_result, "RDX\n");
                    break;
                }
                default:
                    printf("Error: non-existent register");
                    break;
                }
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
            case CMD_JMP:
            {
                fprintf(DisASM_result, "JMP %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JB:
            {
                fprintf(DisASM_result, "JB %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JBE:
            {
                fprintf(DisASM_result, "JBE %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JA:
            {
                fprintf(DisASM_result, "JA %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JAE:
            {
                fprintf(DisASM_result, "JAE %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JE:
            {
                fprintf(DisASM_result, "JE %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
                break;
            }
            case CMD_JNE:
            {
                fprintf(DisASM_result, "JNE %d\n", disasm->code[disasm->IP + 1]);
                disasm->IP += 2;
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