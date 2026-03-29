#ifndef DYNAMIC_ARRAY_H
#include "../lib/utils.h"

#define DYNAMIC_ARRAY_H

struct DynamicArray
{
    void *data;
    int size;
    int capacity;
    enum DATA_TYPE dataType;
};

struct DynamicArray *dynamicArrayCreate(int size, enum DATA_TYPE dataType);
void printArrayElement(enum DATA_TYPE dataType, void *element);
void Add(struct DynamicArray *array, void *elementToAdd);
void Remove(struct DynamicArray *dynamicArray, int elementToRemove);
void PrintArray(struct DynamicArray *array);
void freeDynamicArray(struct DynamicArray *array);
void *elementAtIndex(struct DynamicArray *array, int indexOfElement);

#endif