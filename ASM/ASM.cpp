#include "ASM_UTILS.h"

int main()
{
    ASM_t ASM = {};

    init_ASM(&ASM);
    int err = execute_ASM(&ASM, true );
    if (!err)
    {
        execute_ASM(&ASM, false);
    }
    
    return 0;
}
