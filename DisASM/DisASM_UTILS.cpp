#include "DisASM_UTILS.h"

void init_ASM(DisASM *disasm)
{
    assert(disasm);

    const char *input_filename  = "./Generals/code_machine.bin";

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

    CheckHead(*disasm->head);
}

void execute_ASM(DisASM *disasm)
{

    const char *output_filename = "./DisASM/DisASM Result.txt";

    FILE *DisASM_result = fopen(output_filename, "w");
    
    fprintf(DisASM_result, "%s %d\n", disasm->head->signature, disasm->head->version);

    #define IP     disasm->IP
    #define CMD    disasm->code[IP]
    #define ARG(n) disasm->code[IP + n]

    while(true)
    {
        int a = 0,
            b = 0;
        switch(CMD & cmd_id_mask)
        {
            case CMD_PUSH:
            {   
               if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
                {
                    fprintf(DisASM_result, "PUSH [%d+%s]\n", ARG(1), regs[ARG(2)]);
                    IP++;
                }
                else if ((CMD & With_RAM) && (CMD & With_REG)) fprintf(DisASM_result, "PUSH [%s]\n", regs[ARG(1)]);
                else if ( CMD & With_RAM)                      fprintf(DisASM_result, "PUSH [%d]\n", ARG(1));
                else if ( CMD & With_REG)                      fprintf(DisASM_result, "PUSH %s \n", regs[ARG(1)]);
                else                                           fprintf(DisASM_result, "PUSH %d \n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_ADD:
            {
                fprintf(DisASM_result, "ADD\n");
                IP++;
                break;
            }
            case CMD_SUB:
            {
                fprintf(DisASM_result, "SUB\n");
                IP++;
                break;
            }
            case CMD_MUL:
            {
                fprintf(DisASM_result, "MUL\n");
                IP++;
                break;
            }
            case CMD_DIV:
            {
                fprintf(DisASM_result, "DIV\n");
                IP++;
                break;
            }
            case CMD_DUP:
            {
                fprintf(DisASM_result, "DUP\n");
                IP++;
                break;
            }
            case CMD_OUT:
            {
                fprintf(DisASM_result, "OUT\n");
                IP++;
                break;
            }
            case CMD_JMP:
            {
                fprintf(DisASM_result, "JMP %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JB:
            {
                fprintf(DisASM_result, "JB %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JBE:
            {
                fprintf(DisASM_result, "JBE %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JA:
            {
                fprintf(DisASM_result, "JA %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JAE:
            {
                fprintf(DisASM_result, "JAE %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JE:
            {
                fprintf(DisASM_result, "JE %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_JNE:
            {
                fprintf(DisASM_result, "JNE %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_POP:
            {
                if ((CMD & With_RAM) && (CMD & With_REG) && (CMD & With_PLUS))
                {
                    fprintf(DisASM_result, "POP [%d+%s]\n", ARG(1), regs[ARG(2)]);
                    IP++;
                }
                else if ((CMD & With_RAM) && (CMD & With_REG)) fprintf(DisASM_result, "POP [%s]\n", regs[ARG(1)]);
                else if ( CMD & With_RAM)                      fprintf(DisASM_result, "POP [%d]\n", ARG(1));
                else if ( CMD & With_REG)                      fprintf(DisASM_result, "POP %s \n", regs[ARG(1)]);
                else                                           fprintf(DisASM_result, "POP %d \n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_DUMP:
            {
                fprintf(DisASM_result, "DUMP\n");
                IP++;
                break;
            }
            case CMD_CALL:
            {
                fprintf(DisASM_result, "CALL %d\n", ARG(1));
                IP += 2;
                break;
            }
            case CMD_RET:
            {
                fprintf(DisASM_result, "RET\n");
                IP++;
                break;
            }
            case CMD_PNT:
            {
                fprintf(DisASM_result, "PNT\n");
                IP++;
                break;      
            }
            case CMD_RND:
            {
                fprintf(DisASM_result, "RND\n");
                IP++;
                break; 
            }
            case CMD_SLP:
            {
                fprintf(DisASM_result, "SLP %d\n", ARG(1));
                IP += 2;
                break; 
            }
            case CMD_MTX:
            {
                fprintf(DisASM_result, "MTX\n");
                IP++;
                break; 
            }
            case CMD_COLOR:
            {
                fprintf(DisASM_result, "COLOR %d\n", ARG(1));
                IP += 2;
                break; 
            }
            case CMD_SQR:
            {
                fprintf(DisASM_result, "SQR\n");
                IP++;
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
                fprintf(DisASM_result, "Error. Non-existent command: %d\n", CMD);
                assert(!fclose(DisASM_result));
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