#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DynamicArray
{
    int *data;    // actual data
    int size;     // current amount of items in the array
    int capacity; // maximum amount of items in the array
};
void PrintArray(struct DynamicArray *array);

void Add(struct DynamicArray *array, int elementToAdd)
{
    if (array->size == array->capacity)
    {
        printf("Size of array before resize: %d \n", array->capacity * sizeof(int));
        // TODO Nove the resizng logic outside of this functions
        array->capacity = array->capacity * 2;
        int *temp = realloc(array->data, array->capacity * sizeof(int));
        if (temp == NULL)
        {
            printf("Failed with reallocation of the array \n");
            return;
        }
        array->data = temp;
        printf("Size of array AFTER resize: %d \n", array->capacity * sizeof(int));
    }

    array->data[array->size] = elementToAdd;
    array->size++;
}

void Remove(struct DynamicArray *dynamicArray, int elementToRemove)
{
    // TODO Implement and use binary search
    // TODO Implement reducing the capacity of the array when size == capacity / 2
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
            return;
        }
    }
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
    Remove(dynamicArray, 4);
    PrintArray(dynamicArray);
    printf("Size of array after all elements REMOVED:  %d \n", dynamicArray->capacity * sizeof(int));

    return 0;
}