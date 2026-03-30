#ifndef DYNAMIC_ARRAY_H
#include "../lib/utils.h"

#define DYNAMIC_ARRAY_H

typedef void (*PrintFunc)(const void *item);

typedef struct dynamic_array
{
    void *data;
    int size;
    int capacity;
    size_t elementSize;
    PrintFunc printer;
} DynamicArray;

DynamicArray *dynamicArrayCreate(int capacity, size_t sizeOfElement);
void Add(DynamicArray *array, void *elementToAdd);
void Remove(DynamicArray *array, void *elementToRemove);
void PrintArray(DynamicArray *array);
void freeDynamicArray(DynamicArray *array);
void *elementAtIndex(DynamicArray *array, int indexOfElement);

#endif