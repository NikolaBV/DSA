#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H


struct DynamicArray {
    int *data;
    int size;
    int capacity;
};

struct DynamicArray* createDynamicArray();
void Add(struct DynamicArray *array, int elementToAdd);
void Remove(struct DynamicArray *dynamicArray, int elementToRemove);
void PrintArray(struct DynamicArray *array);
void freeDynamicArray(struct DynamicArray *array);

#endif