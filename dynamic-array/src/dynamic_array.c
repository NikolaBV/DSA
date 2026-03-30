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

void Remove(DynamicArray *array, void *elementToRemove)
{
    // TODO Implement and use binary search
    char *temp = (char *)array->data;

    for (int i = 0; i < array->size; i++)
    {
        char *currentElement = temp + (i * array->elementSize);
        if (memcmp(currentElement, (char *)elementToRemove, array->elementSize) == 0)
        {
            memmove(currentElement, currentElement + array->elementSize, ((array->size - 1) - i) * array->elementSize);
            array->size = array->size - 1;

            if (array->size <= array->capacity / 4)
            {
                resizeArray(array, DIV, 2);
            }
            return;
        }
    }
}

void *elementAtIndex(DynamicArray *array, int indexOfElement)
{
    if (indexOfElement >= array->size)
    {
        printf("Array doesn't have such index ");
        return NULL;
    }
    char *temp = (char *)array->data;
    char *currentElement = temp + (indexOfElement * array->elementSize);
    return (void *)currentElement;
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
    DynamicArray *array = malloc(sizeof(DynamicArray));

    if (array == NULL)
    {
        printf("Allocating memory for dynamic array struct failed \n");
        return NULL;
    }

    array->capacity = capacity;
    array->elementSize = sizeOfElement;
    array->size = 0;

    void *temp = malloc(array->capacity * sizeOfElement);
    if (temp == NULL)
    {
        free(array);
        return NULL;
    }
    array->data = temp;
    return array;
}

void freeDynamicArray(DynamicArray *array)
{
    free(array->data);
    free(array);
}