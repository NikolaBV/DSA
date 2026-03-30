#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../lib/dynamic_array.h"

// TODO Refactor size property of DynamicArray from int => size_t

void resizeArray(DynamicArray *array, arithmeticOperation operation, int amount)
{
    printf("BEFORE RESIZE LOGIC: size of the array %d \n", array->capacity * array->elementSize);

    array->capacity = performArithmetic(operation, array->capacity, amount);

    void *temp = realloc(array->data, array->capacity * array->elementSize);
    if (temp == NULL)
    {
        printf("Failed with reallocation of the array \n");
        return;
    }
    array->data = temp;
    printf("AFTER RESIZE LOGIC size of the array : %d \n", array->capacity * array->elementSize);
}

void Add(DynamicArray *array, void *elementToAdd)
{
    if (array->size == array->capacity)
    {
        resizeArray(array, MUL, 2);
    }
    char *temp = (char *)array->data;
    char *currentElement = temp + (array->size * array->elementSize);
    memcpy(currentElement, elementToAdd, array->elementSize);

    array->size++;
}

// TODO Make generic
//  void Remove(struct DynamicArray *dynamicArray, int elementToRemove)
//  {
//      // TODO Implement and use binary search

//     for (int i = 0; i < dynamicArray->size; i++)
//     {

//         if (dynamicArray->data[i] == elementToRemove)
//         {
//             printf("Element found at index %d, with value %d \n", i, dynamicArray->data[i]);
//             int *locationOfDeletedElement = &dynamicArray->data[i];
//             int *locationRightAfterDeletedElement = &dynamicArray->data[i + 1];
//             int indexOfLastElement = ((dynamicArray->size - 1) - i);
//             memmove(locationOfDeletedElement, locationRightAfterDeletedElement, (indexOfLastElement * sizeof(int)));
//             dynamicArray->size = dynamicArray->size - 1;

//             if (dynamicArray->size <= ceil(dynamicArray->capacity / 2))
//             {
//                 resizeArray(dynamicArray, DIV, 2);
//             }
//             return;
//         }
//     }
// }

// TODO Make this generic

void *elementAtIndex(DynamicArray *array, int indexOfElement)
{
    if (indexOfElement >= array->size)
    {
        printf("Array doesn't have such index ");
        return NULL;
    }
    char *temp = (char *)array->data;
    char *elementToReturn = temp + (indexOfElement * array->elementSize);
    return (void *)elementToReturn;
}

void PrintArray(DynamicArray *array)
{
    if (array == NULL || array->data == NULL)
        return;
    char *temp = array->data;
    for (int i = 0; i < array->size; i++)
    {
        char *currentElement = temp + (i * array->elementSize);
        array->printer(currentElement);
    }
    printf("\n");
}

DynamicArray *dynamicArrayCreate(int capacity, size_t sizeOfElement)
{
    DynamicArray *dynamicArray = malloc(sizeof(DynamicArray));

    if (dynamicArray == NULL)
    {
        printf("Allocating memory for dynamic array struct failed \n");
        return NULL;
    }

    dynamicArray->capacity = capacity;
    dynamicArray->elementSize = sizeOfElement;
    dynamicArray->size = 0;

    void *temp = malloc(dynamicArray->capacity * sizeOfElement);
    if (temp == NULL)
    {
        free(dynamicArray);
        return NULL;
    }
    dynamicArray->data = temp;
    return dynamicArray;
}

void freeDynamicArray(DynamicArray *array)
{
    free(array->data);
    free(array);
}