
#include <stdio.h>
#include <stdlib.h>
#include "../lib/singly-linked-list.h"

struct SLinkedList *singlyLinkedListCreate(size_t elementSize)
{
    struct SLinkedList *linkedList = malloc(sizeof(struct SLinkedList));

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

void InsertAtTail(struct SLinkedList *linkedList, void *dataOfNewNode)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for the new node\n");
        return;
    }

    newNode->data = dataOfNewNode;
    newNode->next = NULL;

    if (linkedList->head == NULL)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    else
    {
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }

    linkedList->length++;
}