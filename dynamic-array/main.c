#include <stdio.h>
#include <stdlib.h>

struct DynamicArray
{
    int *data;
    int size;
    int capacity;
};
void PrintArray(struct DynamicArray *array);

void Add(struct DynamicArray *array, int elementToAdd)
{
    if (array->size == array->capacity)
    {
        printf("Size of array before resize: %d \n", array->capacity * sizeof(int));
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

    for (int i = 0; i < 12; i++)
    {
        Add(dynamicArray, i);
        PrintArray(dynamicArray);
    }

    return 0;
}