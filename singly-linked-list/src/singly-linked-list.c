
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

void InsertAtHead(struct SLinkedList *linkedList, void *dataOfNewNode)
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Couldn't allocate space for a node\n");
        return;
    }

    newNode->data = dataOfNewNode;

    if (linkedList->head == NULL)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
        linkedList->length++;
    }
    else
    {
        struct Node *previousHead = linkedList->head;
        linkedList->head = newNode;
        newNode->next = previousHead;
    }
}
struct Node *InsertAtIndex(struct SLinkedList *linkedList, void *dataOfNewNode, int index)
{

    if (linkedList->head == NULL)
    {
        printf("Can't insert at index of an empty linked list \n");
        return NULL;
    }
    struct Node *elementAtIndex = findNodeInListAtIndex(linkedList, 1);

    if (elementAtIndex == NULL)
    {
        return NULL;
    }
    int *dataPtr = (int *)elementAtIndex->data;
    printf("Value node at index 1 is: %zu\n", dataPtr);
    return elementAtIndex;
}

struct Node *findNodeInListAtIndex(struct SLinkedList *list, int index)
{
    int counter = 0;
    struct Node *node = list->head;

    while (counter != index)
    {
        node = node->next;

        if (node == NULL)
        {
            printf("Undex is out of bounds of the list \n");
            return NULL;
        }

        index++;
    }
    return node;
}