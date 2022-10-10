#include "ASM_UTILS.h"

int main()
{
    Text input_data = {};

    init_ASM(&input_data);

    execute_ASM(input_data);

    return 0;
}
