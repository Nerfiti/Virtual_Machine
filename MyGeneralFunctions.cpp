#include "MyGeneralFunctions.h"
#include "assert.h"

const void *const JUST_FREE_PTR = "JUST_FREE";

void MG_qsort(void *arr, size_t arr_size, size_t item_size, comp_t comp)
{
    assert(arr != nullptr);

    if (arr_size <= item_size)
    {
        return;
    }

    int last = 1;
    char *array = (char *)arr;

    for (int i = 1; i < arr_size/item_size; ++i)
    {
        if (comp(array, array + i*item_size) > 0)
        {
            MG_swap(array + i*item_size, array + last*item_size, item_size);
            last++;
        }
    }
    MG_swap(array, array + (last - 1)*item_size, item_size);
    MG_qsort(array, (last-1)*item_size, item_size, comp);
    MG_qsort(array + last*item_size, arr_size - last*item_size, item_size, comp);
}

void MG_swap(void *item1, void *item2, size_t item_size)
{
    char *ITEM1 = (char *)item1;
    char *ITEM2 = (char *)item2;
    for (int i = 0; i < item_size; ++i)
    {
        char temp = *(ITEM1 + i);
        *(ITEM1 + i) = *(ITEM2 + i);
        *(ITEM2 + i) = temp;
    }
}