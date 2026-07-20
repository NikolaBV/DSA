#include <stdio.h>
#include "lib/doubly-linked-list.h"
int main()
{
    DLinkedList *linkedList = doublyLinkedListCreate(sizeof(int));
    InsertAtTail(linkedList, (void *)(intptr_t)1);
    InsertAtTail(linkedList, (void *)(intptr_t)2);
    InsertAtTail(linkedList, (void *)(intptr_t)3);
    InsertAtIndex(linkedList, (void *)(intptr_t)1000, 1);

    printf("value of head is: %d\n", (int *)linkedList->head->next->next->data);
}