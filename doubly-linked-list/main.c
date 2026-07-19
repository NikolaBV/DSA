#include <stdio.h>
#include "lib/doubly-linked-list.h"
int main()
{
    DLinkedList *linkedList = doublyLinkedListCreate(sizeof(int));
    InsertAtTail(linkedList, (void *)(intptr_t)1);
    InsertAtTail(linkedList, (void *)(intptr_t)2);
    UpdateAtIndex(linkedList, (void *)(intptr_t)100, 0);

    printf("value of head is: %d\n", (int *)linkedList->head->data);
    printf("Updated value of head to be 100: : %d\n", (int *)linkedList->head->data);
    printf("value of head.next is: %d\n", (int *)linkedList->head->next->data);
    printf("value of tail.prev is: %d\n", (int *)linkedList->tail->prev->data);
}