#include "lib/singly-linked-list.h"

#include <stdio.h>
#include <stdlib.h>

static int *heap_int(int value)
{
    int *p = malloc(sizeof(int));
    *p = value;
    return p;
}

static int sumNodeValues(void *data, void *context)
{
    *(int *)context += *(int *)data;
    return 0;
}

static int printData(void *data, void *context)
{
    int *count = (int *)context;
    printf("[%d] %d, ", *count, *(int *)data);
    *count += 1;
    return 0;
}

static int compareInts(void *firstNumber, void *secondNumber)
{
    return *(int *)firstNumber - *(int *)secondNumber;
}

int main(void)
{
    int count = 0;
    SllList *linkedList = sll_create(sizeof(int));
    if (linkedList == NULL)
    {
        printf("Couldn't allocate memory for the list\n");
        return 1;
    }

    for (int i = 1; i <= 3; i++)
    {
        sll_push_back(linkedList, heap_int(i));
        count = 0;
        sll_traverse(linkedList, printData, &count);
        printf("\n");
    }

    int total = 0;
    sll_traverse(linkedList, sumNodeValues, &total);
    printf("Sum of all values: %d\n", total);

    int needle = 2;
    void *found = NULL;
    if (sll_find(linkedList, &needle, compareInts, &found) == 0)
    {
        printf("Found: %d\n", *(int *)found);
    }

    printf("First node is: %d\n", *(int *)linkedList->head->data);

    sll_reverse(linkedList);
    printf("After reverse: \n");
    count = 0;
    sll_traverse(linkedList, printData, &count);
    printf("\n");

    sll_destroy(linkedList, free);
    return 0;
}
