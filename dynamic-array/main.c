#include "lib/dynamic_array.h"
#include <stdio.h>

static void print_int(const void *element)
{
    printf("%d ", *(const int *)element);
}

int main(void)
{
    DynamicArray *dynamicArray = da_create(3, sizeof(int));

    if (dynamicArray == NULL)
    {
        fprintf(stderr, "Failed to create array. Out of memory!\n");
        return 1;
    }

    dynamicArray->printer = print_int;

    for (int i = 0; i < 5; i++)
    {
        da_push_back(dynamicArray, &i);
        da_print(dynamicArray);
    }

    for (int i = 0; i < 5; i++)
    {
        da_remove_value(dynamicArray, &i);
        da_print(dynamicArray);
    }

    printf("Capacity in bytes after all elements removed: %zu\n",
           (size_t)dynamicArray->capacity * sizeof(int));

    da_destroy(dynamicArray);
    return 0;
}
