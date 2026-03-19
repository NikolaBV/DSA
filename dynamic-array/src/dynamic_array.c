#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../lib/dynamic_array.h"

enum ArithmeticOperation { ADD, SUB, MUL, DIV };

static int performArithmetic(enum ArithmeticOperation operation, int first, int second) {
    switch (operation) {
        case ADD: return first + second;
        case MUL: return first * second;
        case DIV: return first / second;
        default:  return first;
    }
}
struct DynamicArray
{
    int *data;    // actual data
    int size;     // current amount of items in the array
    int capacity; // maximum amount of items in the array
};



void resizeArray(struct DynamicArray *array, enum ArithmeticOperation operation, int amount)
{

    array->capacity = performArithmetic(operation, array->capacity, amount);

    int *temp = realloc(array->data, array->capacity * sizeof(int));
    if (temp == NULL)
    {
        printf("Failed with reallocation of the array \n");
        return;
    }
    array->data = temp;
}

void Add(struct DynamicArray *array, int elementToAdd)
{
    if (array->size == array->capacity)
    {
        resizeArray(array, MUL, 2);
    }

    array->data[array->size] = elementToAdd;
    array->size++;
}

void Remove(struct DynamicArray *dynamicArray, int elementToRemove)
{
    // TODO Implement and use binary search
    for (int i = 0; i < dynamicArray->size; i++)
    {

        if (dynamicArray->data[i] == elementToRemove)
        {
            printf("Element found at index %d, with value %d \n", i, dynamicArray->data[i]);
            int *locationOfDeletedElement = &dynamicArray->data[i];
            int *locationRightAfterDeletedElement = &dynamicArray->data[i + 1];
            int indexOfLastElement = ((dynamicArray->size - 1) - i);
            memmove(locationOfDeletedElement, locationRightAfterDeletedElement, (indexOfLastElement * sizeof(int)));
            dynamicArray->size = dynamicArray->size - 1;

            if (dynamicArray->size <= ceil(dynamicArray->capacity / 2))
            {
                resizeArray(dynamicArray, DIV, 2);
            }
            return;
        }
    }
}

int elementAtIndex(struct DynamicArray *dynamicArray, int element)
{
    return dynamicArray->data[element];
}

void PrintArray(struct DynamicArray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        printf("%d, ", array->data[i]);
    }
    printf("\n");
}

struct DynamicArray *createDynamicArray()
{
    struct DynamicArray *dynamicArray = malloc(sizeof(struct DynamicArray));
    const int CAPACITY = 5;

    dynamicArray->capacity = CAPACITY;
    dynamicArray->size = 0;
    int *temp = malloc(dynamicArray->capacity * sizeof(int));
    if (temp == NULL)
    {
        free(dynamicArray);
        return NULL;
    }
    dynamicArray->data = temp;
    return dynamicArray;
}
