#include "lib/dynamic_array.h"
#include <stdio.h>

int main()
{
    DynamicArray *dynamicArray = dynamicArrayCreate(5, sizeof(int));
    dynamicArray->printer = printInt;

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

    int *secondElement = elementAtIndex(dynamicArray, 1);
    printf("Element at index 1 is: %d", *secondElement);
    // Remove(dynamicArray, 0);
    // PrintArray(dynamicArray);
    // printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    freeDynamicArray(dynamicArray);
    return 0;
}