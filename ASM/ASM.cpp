#include "ASM_UTILS.h"

int main(const int argc, const char *argv[])
{
    ProgMode mode = getProgramMode(argc, argv);
    if (mode & WrongMode)
    {
        printf("Wrong program mode.\n\n");
        system("type README.md");
        return 0;
    }

    ASM_t ASM = {};

    init_ASM(&ASM);

    int err = execute_ASM(&ASM, true);
    if (!err)
    {
        execute_ASM(&ASM, false);
    }

    if (mode & O9)
    {
        optimizeExecute(&ASM);
    }

    PrintCode(ASM.code, ASM.ip);
    ASM_Dtor(&ASM);

    return 0;
}
