#include "lib/singly-linked-list.h"
#include <stdint.h>

int sumNodeValues(void *data, void *context)
{
    int *currentTotal = (int *)context;
    struct Node *node = (struct Node *)data;

    *currentTotal += (int)(intptr_t)node->data;
    return 0;
}

int printData(void *data, void *context)
{
    int *count = (int *)context;
    struct Node *node = (struct Node *)data;
    printf("[%d] %d, ", *count, (int *)(intptr_t)node->data);
    *count += 1;

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
    int count = 0;
    struct SLinkedList *linkedList = singlyLinkedListCreate(sizeof(int));
    if (linkedList == NULL)
    {
        free(linkedList);
        printf("Couldn't allocate memory for the new node\n");
        return -1;
    }

    InsertAtTail(linkedList, (void *)(intptr_t)1);
    Traverse(linkedList, printData, &count);
    printf("\n");

    InsertAtTail(linkedList, (void *)(intptr_t)2);
    Traverse(linkedList, printData, &count);
    printf("\n");

    InsertAtTail(linkedList, (void *)(intptr_t)3);
    Traverse(linkedList, printData, &count);
    printf("\n");

    count = 0;

    int *firstNode = (int *)linkedList->head->data;

    printf("First node is: %d\n", firstNode);
    reverse(linkedList);
    printf("After reverse: \n");
    Traverse(linkedList, printData, &count);
    printf("\n");
}