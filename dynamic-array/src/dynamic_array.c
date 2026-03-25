#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../lib/dynamic_array.h"

// TODO Use free() to clean up the array either on user demand or after no more elements are left after removing
// TODO Refactor size property of DynamicArray from int => size_t

int sizeOfDataType(enum DATA_TYPE dataType)
{
    switch (dataType)
    {
    case INT:
        return sizeof(int);
    case FLOAT:
        return sizeof(float);

    case CHAR:
        return sizeof(char);

    default:
        return -1;
    }
}

static int performArithmetic(enum ArithmeticOperation operation, int first, int second)
{
    switch (operation)
    {
    case ADD:
        return first + second;
    case MUL:
        return first * second;
    case DIV:
        return first / second;
    default:
        return first;
    }
}
struct DynamicArray
{
    void *data;
    int size;
    int capacity;
    enum DATA_TYPE dataType;
};

void resizeArray(struct DynamicArray *array, enum ArithmeticOperation operation, int amount)
{

    array->capacity = performArithmetic(operation, array->capacity, amount);

    void *temp = realloc(array->data, array->capacity * sizeof(sizeOfDataType(array->dataType)));
    if (temp == NULL)
    {
        printf("Failed with reallocation of the array \n");
        return;
    }
    array->data = temp;
}

// TODO Figure out how to make this generic, ive found 2 options so far:
// 1, Cast the void* to a specific type
// 2. Use memcpy and calculate manually the index where you need to place the new element
void Add(struct DynamicArray *array, void *elementToAdd)
{
    if (array->size == array->capacity)
    {
        resizeArray(array, MUL, 2);
    }

    array->data[array->size] = elementToAdd;
    array->size++;
}

// void Remove(struct DynamicArray *dynamicArray, int elementToRemove)
// {
//     // TODO Implement and use binary search
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

// int elementAtIndex(struct DynamicArray *dynamicArray, int element)
// {
//     return dynamicArray->data[element];
// }

// void PrintArray(struct DynamicArray *array)
// {
//     for (int i = 0; i < array->size; i++)
//     {
//         printf("%d, ", array->data[i]);
//     }
//     printf("\n");
// }

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

    int bytesOfDataType = 0;

    void *temp = malloc(dynamicArray->capacity * sizeof(bytesOfDataType));
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
    // TODO Implement
}