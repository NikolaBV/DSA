
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
    }
    else
    {
        struct Node *previousHead = linkedList->head;
        linkedList->head = newNode;
        newNode->next = previousHead;
    }
    linkedList->length++;
}
void UpdateAtIndex(struct SLinkedList *list, void *newDataToInsertIntoNode, int index)
{

    if (list->head == NULL)
    {
        printf("Can't insert at index of an empty linked list \n");
        return;
    }
    struct Node *elementAtIndex = findNodeInListAtIndex(list, index);

    if (elementAtIndex == NULL)
    {
        return;
    }

    elementAtIndex->data = newDataToInsertIntoNode;
}
void InsertAtIndex(struct SLinkedList *list, void *data, int index)
{
    if (index < 0 || index > list->length)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (index == 0)
    {
        InsertAtHead(list, data);
        return;
    }
    if (index == list->length)
    {
        InsertAtTail(list, data);
        return;
    }

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;

    struct Node *prev = findNodeInListAtIndex(list, index - 1);

    newNode->next = prev->next;
    prev->next = newNode;

    list->length++;
}

void DeleteHead(struct SLinkedList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete head: List is empty.\n");
        return;
    }

    struct Node *oldHead = list->head;
    list->head = oldHead->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    list->length--;

    free(oldHead);
    printf("Head deleted. New length: %d\n", list->length);
}

void DeleteTail(struct SLinkedList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete: List is empty.\n");
        return;
    }

    struct Node *oldTail = list->tail;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        struct Node *newTail = findNodeInListAtIndex(list, list->length - 2);
        list->tail = newTail;
        list->tail->next = NULL;
    }

    free(oldTail);
    list->length--;
    printf("Tail deleted. New length: %d\n", list->length);
}

struct Node *findNodeInListAtIndex(struct SLinkedList *list, int index)
{
    if (index < 0 || index >= list->length)
    {
        printf("Index out of bounds\n");
        return NULL;
    }
    struct Node *node = list->head;
    for (int i = 0; i < list->length; i++)
    {
        if (i == index)
        {
            printf("Found element at index %d with value %d\n", i, node->data);
            return node;
        }
        else
        {
            node = node->next;
        }
    }
    return NULL;
}
