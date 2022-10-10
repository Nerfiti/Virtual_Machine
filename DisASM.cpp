#include "DisASM_UTILS.h"

const int version_CPU = 2;

int main()
{  
    DisASM disasm = {};

    init_ASM(&disasm);

    execute_ASM(&disasm);

    return 0;
}