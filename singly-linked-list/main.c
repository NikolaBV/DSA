#include "lib/singly-linked-list.h"
#include <stdint.h>

int sumNodeValues(void *data, void *context)
{
    int *currentTotal = (int *)context;
    struct Node *node = (struct Node *)data;

    *currentTotal += (int)(intptr_t)node->data;
    return 0;
}

int compareInts(void *firstNumber, void *secondNumber)
{
    int firstNumberCasted = (int)(intptr_t)firstNumber;
    int secondNumberCasted = (int)(intptr_t)secondNumber;

    if (firstNumberCasted == secondNumberCasted)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    struct SLinkedList *linkedList = singlyLinkedListCreate(sizeof(int));
    if (linkedList == NULL)
    {
        free(linkedList);
        printf("Couldn't allocate memory for the new node\n");
        return -1;
    }

    InsertAtTail(linkedList, (void *)(intptr_t)1);
    InsertAtTail(linkedList, (void *)(intptr_t)2);
    InsertAtTail(linkedList, (void *)(intptr_t)3);

    int *firstNode = (int *)linkedList->head->data;
    int *secondNode = (int *)linkedList->head->next->data;

    int sum = 0;

    Traverse(linkedList, sumNodeValues, &sum);

    printf("First node: %d\n", firstNode);
    printf("Sum of all nodes is: %d\n", sum);

    void *result;
    if (find(linkedList, (void *)(intptr_t)4, compareInts, &result) == 0)
    {
        printf("Result data: %d", (void *)(intptr_t)result);
    }
}