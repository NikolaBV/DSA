#include "lib/dynamic_array.h"
#include <stdio.h>

// TODO Add proper error handling in every function
// TODO After implemnting all functions for the array, work on making it generic (void *)
// TODO Use free() to clean up the array either on user demand or after no more elements are left after removing

int main() {
   struct DynamicArray *dynamicArray = createDynamicArray();
    if (dynamicArray == NULL)
    {
        fprintf(stderr, "Failed to create array. Out of memory!\n");
        return 1;
    }
    printf("Initial size of the array %d \n", dynamicArray->capacity * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        Add(dynamicArray, i);
        PrintArray(dynamicArray);
    }
    printf("Size of array after all elements added:  %d \n", dynamicArray->capacity * sizeof(int));
    Remove(dynamicArray, 0);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 1);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 2);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 3);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 4);
    PrintArray(dynamicArray);
    printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    return 0;
}