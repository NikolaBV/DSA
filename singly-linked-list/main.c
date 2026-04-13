#include "lib/singly-linked-list.h"
#include <stdint.h>

int sumNodeValues(void *data, void *context)
{
    int *currentTotal = (int *)context;
    int value = (int)(intptr_t)data;

    *currentTotal += value;
    return 0;
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

    free(linkedList);
}