#include "lib/singly-linked-list.h"
#include <stdint.h>

int main()
{
    struct SLinkedList *linkedList = singlyLinkedListCreate(sizeof(int));
    if (linkedList == NULL)
    {
        free(linkedList);
        printf("Couldn't allocate memory for the new node");
        return -1;
    }

    InsertAtTail(linkedList, (void *)(intptr_t)1);
    InsertAtTail(linkedList, (void *)(intptr_t)2);

    InsertAtIndex(linkedList, (void *)(intptr_t)200, 0);

    int *firstNode = (int *)linkedList->head->data;
    int *secondNode = (int *)linkedList->head->next->data;

    printf("Value of node 1 is: %zu\n", firstNode);
    printf("Value of node 2 is: %zu\n", secondNode);

    free(linkedList);
}