#include <stdio.h>
#include "lib/doubly-linked-list.h"
int main()
{
    struct DLinkedList *linkedList = doublyLinkedListCreate(sizeof(int));
    InsertAtTail(linkedList, (void *)(intptr_t)1);
    InsertAtTail(linkedList, (void *)(intptr_t)2);

    printf("value of head is: %d", (int *)linkedList->head->data);
    printf("value of head.next is: %d", (int *)linkedList->head->next->data);
    printf("value of tail.prev is: %d", (int *)linkedList->tail->prev->data);
}