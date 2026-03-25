#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

enum ArithmeticOperation
{
    ADD,
    SUB,
    MUL,
    DIV
};
enum DATA_TYPE
{
    INT,
    FLOAT,
    CHAR,
};

struct DynamicArray
{
    void *data;
    int size;
    int capacity;
    enum DATA_TYPE dataType;
};

struct DynamicArray *dynamicArrayCreate(int size, enum DATA_TYPE dataType);
void Add(struct DynamicArray *array, void *elementToAdd);
void Remove(struct DynamicArray *dynamicArray, int elementToRemove);
void PrintArray(struct DynamicArray *array);
void freeDynamicArray(struct DynamicArray *array);

#endif