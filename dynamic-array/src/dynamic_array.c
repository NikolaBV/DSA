#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../lib/dynamic_array.h"

// TODO Refactor size property of DynamicArray from int => size_t

void printArrayElement(enum DATA_TYPE dataType, void *indexOfElement)
{
    switch (dataType)
    {
    case INT:
        printf("%d, ", *(int *)indexOfElement);
        break;
    case FLOAT:
        printf("%f, ", *(float *)indexOfElement);
        break;

    case CHAR:
        printf("%s, ", *(char *)indexOfElement);
        break;

    default:
        return;
    }
}
void resizeArray(struct DynamicArray *array, enum ArithmeticOperation operation, int amount)
{
    printf("BEFORE RESIZE LOGIC: size of the array %d \n", array->capacity * sizeOfDataType(array->dataType));

    array->capacity = performArithmetic(operation, array->capacity, amount);

    void *temp = realloc(array->data, array->capacity * sizeOfDataType(array->dataType));
    if (temp == NULL)
    {
        printf("Failed with reallocation of the array \n");
        return;
    }
    array->data = temp;
    printf("AFTER RESIZE LOGIC size of the array : %d \n", array->capacity * sizeOfDataType(array->dataType));
}

void Add(struct DynamicArray *array, void *elementToAdd)
{
    if (array->size == array->capacity)
    {
        resizeArray(array, MUL, 2);
    }
    char *temp = (char *)array->data;
    char *newAddress = temp + (array->size * sizeOfDataType(array->dataType));
    memcpy(newAddress, elementToAdd, sizeOfDataType(array->dataType));
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

void *elementAtIndex(struct DynamicArray *array, int indexOfElement)
{
    if (indexOfElement > array->size)
    {
        printf("Array doesn't have such index ");
        return NULL;
    }
    char *temp = (char *)array->data;
    return *(temp + (indexOfElement * sizeOfDataType(array->dataType)));
}

void PrintArray(struct DynamicArray *array)
{
    char *temp = (char *)array->data;
    for (int i = 0; i < array->size; i++)
    {
        char *newAddress = temp + (i * sizeOfDataType(array->dataType));
        printArrayElement(array->dataType, newAddress);
    }
    printf("\n");
}

struct DynamicArray *dynamicArrayCreate(int capacity, enum DATA_TYPE dataType)
{
    struct DynamicArray *dynamicArray = malloc(sizeof(struct DynamicArray));

    if (dynamicArray == NULL)
    {
        printf("Allocating memory for dynamic array struct failed \n");
        return NULL;
    }

    dynamicArray->capacity = capacity;
    dynamicArray->size = 0;

    int bytesOfDataType = sizeOfDataType(dataType);

    void *temp = malloc(dynamicArray->capacity * bytesOfDataType);
    if (temp == NULL)
    {
        free(dynamicArray);
        return NULL;
    }
    dynamicArray->data = temp;
    return dynamicArray;
}

void freeDynamicArray(struct DynamicArray *array)
{
    free(array->data);
    free(array);
}