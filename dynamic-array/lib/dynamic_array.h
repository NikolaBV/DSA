#ifndef DYNAMIC_ARRAY_H
#include "../lib/utils.h"

#define DYNAMIC_ARRAY_H

typedef void (*PrintFunc)(const void *item);

struct DynamicArray
{
    void *data;
    int size;
    int capacity;
    size_t elementSize;
    PrintFunc printer;
};

struct DynamicArray *dynamicArrayCreate(int capacity, size_t sizeOfElement);
void Add(struct DynamicArray *array, void *elementToAdd);
void Remove(struct DynamicArray *dynamicArray, int elementToRemove);
void PrintArray(struct DynamicArray *array);
void freeDynamicArray(struct DynamicArray *array);
void *elementAtIndex(struct DynamicArray *array, int indexOfElement);

#endif