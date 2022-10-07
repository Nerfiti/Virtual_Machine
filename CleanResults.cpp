#include <assert.h>
#include <cstdio>
#include <errno.h>

int main()
{
    remove("./DisASM Result.txt");
    remove("./Listing.txt");
    remove("./Result.txt");
    return 0;
}