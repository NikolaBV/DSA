#include "lib/dynamic_array.h"
#include <stdio.h>

int main()
{
    struct DynamicArray *dynamicArray = dynamicArrayCreate(3, INT);
    if (dynamicArray == NULL)
    {
        fprintf(stderr, "Failed to create array. Out of memory!\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
    {
        Add(dynamicArray, (void *)&i);
        PrintArray(dynamicArray);
    }
    // Remove(dynamicArray, 0);
    // PrintArray(dynamicArray);
    // printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    return 0;
}