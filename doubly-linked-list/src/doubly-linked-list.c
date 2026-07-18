#include "../lib/doubly-linked-list.h"
DLinkedList *doublyLinkedListCreate(size_t elementSize)
{
    DLinkedList *linkedList = malloc(sizeof(DLinkedList));

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

void InsertAtTail(DLinkedList *linkedList, void *dataOfNewNode)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for the new node \n");
        free(newNode);
        return;
    }

    newNode->data = dataOfNewNode;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (linkedList->head == NULL)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        linkedList->tail->next = newNode;
        linkedList->tail->next->prev = linkedList->tail;
        linkedList->tail = newNode;
    }
    linkedList->length++;
}

void InsertAtHead(DLinkedList *linkedList, void *dataOfNewNode)
{
}