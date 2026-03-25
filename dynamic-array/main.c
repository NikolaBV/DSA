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
    printf("Initial size of the array %d \n", dynamicArray->capacity * sizeof(int));

    // for (int i = 0; i < 5; i++)
    // {
    //     Add(dynamicArray, i);
    //     PrintArray(dynamicArray);
    // }
    // printf("Size of array after all elements added:  %d \n", dynamicArray->capacity * sizeof(int));
    // Remove(dynamicArray, 0);
    // PrintArray(dynamicArray);
    // Remove(dynamicArray, 1);
    // PrintArray(dynamicArray);
    // Remove(dynamicArray, 2);
    // PrintArray(dynamicArray);
    // Remove(dynamicArray, 3);
    // PrintArray(dynamicArray);
    // Remove(dynamicArray, 4);
    // PrintArray(dynamicArray);
    // printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    return 0;
}