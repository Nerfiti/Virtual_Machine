#include "CPU_UTILS.h"

int main()
{  
    SoftCPU CPU = {};
    
    init_CPU(&CPU);
    
    execute_CPU(&CPU);
    
    return 0;
}
