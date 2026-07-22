#include "../lib/dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO Refactor size/capacity of DynamicArray from int => size_t

static void da_resize(DynamicArray *array, int newCapacity)
{
    void *temp = realloc(array->data, (size_t)newCapacity * array->elementSize);
    if (temp == NULL)
    {
        printf("Failed with reallocation of the array\n");
        return;
    }

    array->capacity = newCapacity;
    array->data = temp;
}

DynamicArray *da_create(int capacity, size_t elementSize)
{
    DynamicArray *array = malloc(sizeof(DynamicArray));

    if (array == NULL)
    {
        printf("Allocating memory for dynamic array struct failed\n");
        return NULL;
    }

    array->capacity = capacity;
    array->elementSize = elementSize;
    array->size = 0;
    array->printer = NULL;

    void *temp = malloc((size_t)capacity * elementSize);
    if (temp == NULL)
    {
        free(array);
        return NULL;
    }
    array->data = temp;
    return array;
}

void da_destroy(DynamicArray *array)
{
    if (array == NULL)
        return;

    free(array->data);
    free(array);
}

void da_push_back(DynamicArray *array, void *elementToAdd)
{
    if (array->size == array->capacity)
    {
        da_resize(array, array->capacity * 2);
    }

    char *temp = (char *)array->data;
    char *currentElement = temp + ((size_t)array->size * array->elementSize);
    memcpy(currentElement, elementToAdd, array->elementSize);

    array->size++;
}

void da_remove_value(DynamicArray *array, void *elementToRemove)
{
    // TODO Implement and use binary search
    char *temp = (char *)array->data;

    for (int i = 0; i < array->size; i++)
    {
        char *currentElement = temp + ((size_t)i * array->elementSize);
        if (memcmp(currentElement, elementToRemove, array->elementSize) == 0)
        {
            memmove(currentElement,
                    currentElement + array->elementSize,
                    (size_t)((array->size - 1) - i) * array->elementSize);
            array->size = array->size - 1;

            if (array->size <= array->capacity / 4)
            {
                da_resize(array, array->capacity / 2);
            }
            return;
        }
    }
}

void *da_at(DynamicArray *array, int index)
{
    if (index >= array->size)
    {
        printf("Array doesn't have such index\n");
        return NULL;
    }

    char *temp = (char *)array->data;
    return temp + ((size_t)index * array->elementSize);
}

void da_print(DynamicArray *array)
{
    if (array == NULL || array->data == NULL || array->printer == NULL)
        return;

    char *temp = array->data;
    for (int i = 0; i < array->size; i++)
    {
        char *currentElement = temp + ((size_t)i * array->elementSize);
        array->printer(currentElement);
    }
    printf("\n");
}
