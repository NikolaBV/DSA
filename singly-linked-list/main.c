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
    InsertAtTail(linkedList, (void *)(intptr_t)3);

    int *firstNode = (int *)linkedList->head->data;
    int *secondNode = (int *)linkedList->head->next->data;

    DeleteAtIndex(linkedList, 0);

    free(linkedList);
}