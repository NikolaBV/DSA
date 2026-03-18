#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// TODO Add proper error handling in every function
// TODO After implemnting all functions for the array, work on making it generic (void *)
// TODO Use free() to clean up the array either on user demand or after no more elements are left after removing
struct DynamicArray
{
    int *data;    // actual data
    int size;     // current amount of items in the array
    int capacity; // maximum amount of items in the array
};

enum ArithmeticOperation
{
    ADD,
    SUB,
    MUL,
    DIV
};

int performArithmetic(enum ArithmeticOperation operation, int firstNumber, int secondNumber)
{
    switch (operation)
    {
    ADD:
        return firstNumber + secondNumber;
        break;
    SUB:
        return firstNumber - secondNumber;

        break;
    MUL:
        return firstNumber * secondNumber;

        break;
    DIV:
        return firstNumber / secondNumber;

        break;
    }
}

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

int main()
{
    struct DynamicArray *dynamicArray = createDynamicArray();
    if (dynamicArray == NULL)
    {
        fprintf(stderr, "Failed to create array. Out of memory!\n");
        return 1;
    }
    printf("Initial size of the array %d \n", dynamicArray->capacity * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        Add(dynamicArray, i);
        PrintArray(dynamicArray);
    }
    printf("Size of array after all elements added:  %d \n", dynamicArray->capacity * sizeof(int));
    Remove(dynamicArray, 0);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 1);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 2);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 3);
    PrintArray(dynamicArray);
    Remove(dynamicArray, 4);
    PrintArray(dynamicArray);
    printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    return 0;
}