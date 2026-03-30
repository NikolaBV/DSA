#include "lib/dynamic_array.h"
#include <stdio.h>

int main()
{
    DynamicArray *dynamicArray = dynamicArrayCreate(3, sizeof(int));
    dynamicArray->printer = printInt;

    if (dynamicArray == NULL)
    {
        fprintf(stderr, "Failed to create array. Out of memory!\n");
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        Add(dynamicArray, (void *)&i);
        PrintArray(dynamicArray);
    }

    for (int i = 0; i < 5; i++)
    {
        Remove(dynamicArray, (void *)&i);
        PrintArray(dynamicArray);
    }

    printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    freeDynamicArray(dynamicArray);
    return 0;
}