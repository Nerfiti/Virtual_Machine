#include "ASM_UTILS.h"

int main()
{
    ASM_t ASM = {};

    init_ASM(&ASM);

    execute_ASM(&ASM, true );
    execute_ASM(&ASM, false);

    return 0;
}
