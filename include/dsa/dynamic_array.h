#pragma once

#include <stddef.h>

typedef void (*DaPrintFn)(const void *element);

typedef struct dynamic_array
{
    void *data;
    int size;
    int capacity;
    size_t elementSize;
    DaPrintFn printer;
} DynamicArray;

DynamicArray *da_create(int capacity, size_t elementSize);
void da_destroy(DynamicArray *array);
void da_push_back(DynamicArray *array, void *element);
void da_remove_value(DynamicArray *array, void *element);
void *da_at(DynamicArray *array, int index);
void da_print(DynamicArray *array);
