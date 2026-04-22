#include "../lib/doubly-linked-list.h"
struct DLinkedList *doublyLinkedListCreate(size_t elementSize)
{
    struct DLinkedList *linkedList = malloc(sizeof(struct DLinkedList));

    if (linkedList == NULL)
    {
        printf("Couldn't allocate memory for linked list");
        return NULL;
    }

    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->length = 0;
    linkedList->elementSize = elementSize;

    return linkedList;
}