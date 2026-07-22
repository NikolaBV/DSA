#include "dsa/singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static SllNode *sll_node_at(SllList *list, int index)
{
    if (index < 0 || (size_t)index >= list->length)
    {
        return NULL;
    }

    SllNode *node = list->head;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    return node;
}

SllList *sll_create(size_t elementSize)
{
    SllList *linkedList = malloc(sizeof(SllList));

    if (linkedList == NULL)
    {
        printf("Couldn't allocate memory for linked list\n");
        return NULL;
    }

    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->length = 0;
    linkedList->elementSize = elementSize;

    return linkedList;
}

void sll_push_back(SllList *linkedList, void *dataOfNewNode)
{
    SllNode *newNode = malloc(sizeof(SllNode));
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

void sll_push_front(SllList *linkedList, void *dataOfNewNode)
{
    SllNode *newNode = malloc(sizeof(SllNode));
    if (newNode == NULL)
    {
        printf("Couldn't allocate space for a node\n");
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
        SllNode *previousHead = linkedList->head;
        linkedList->head = newNode;
        newNode->next = previousHead;
    }
    linkedList->length++;
}

void sll_set_at(SllList *list, void *newDataToInsertIntoNode, int index)
{
    if (list->head == NULL)
    {
        printf("Can't insert at index of an empty linked list\n");
        return;
    }

    SllNode *elementAtIndex = sll_node_at(list, index);

    if (elementAtIndex == NULL)
    {
        printf("Index out of bounds\n");
        return;
    }

    elementAtIndex->data = newDataToInsertIntoNode;
}

void sll_insert_at(SllList *list, void *data, int index)
{
    if (index < 0 || (size_t)index > list->length)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (index == 0)
    {
        sll_push_front(list, data);
        return;
    }

    if ((size_t)index == list->length)
    {
        sll_push_back(list, data);
        return;
    }

    SllNode *newNode = malloc(sizeof(SllNode));
    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for the new node\n");
        return;
    }
    newNode->data = data;

    SllNode *prev = sll_node_at(list, index - 1);

    newNode->next = prev->next;
    prev->next = newNode;

    list->length++;
}

void sll_pop_front(SllList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete head: List is empty.\n");
        return;
    }

    SllNode *oldHead = list->head;
    list->head = oldHead->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    list->length--;

    free(oldHead);
}

void sll_pop_back(SllList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete: List is empty.\n");
        return;
    }

    SllNode *oldTail = list->tail;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        SllNode *newTail = sll_node_at(list, (int)list->length - 2);
        list->tail = newTail;
        list->tail->next = NULL;
    }

    free(oldTail);
    list->length--;
}

void sll_remove_at(SllList *list, int index)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete: List is empty.\n");
        return;
    }
    if (index == 0)
    {
        sll_pop_front(list);
        return;
    }
    if ((size_t)index == list->length - 1)
    {
        sll_pop_back(list);
        return;
    }

    SllNode *previous = sll_node_at(list, index - 1);
    if (previous == NULL || previous->next == NULL)
    {
        printf("Index out of bounds\n");
        return;
    }

    SllNode *elementToDelete = previous->next;
    previous->next = elementToDelete->next;
    free(elementToDelete);
    list->length--;
}

void sll_traverse(SllList *list, int (*callback)(void *data, void *context), void *context)
{
    SllNode *currentNode = list->head;

    while (currentNode != NULL)
    {
        SllNode *nextNode = currentNode->next;

        if (callback(currentNode->data, context))
            break;

        currentNode = nextNode;
    }
}

void sll_destroy(SllList *list, void (*dataDestructor)(void *data))
{
    if (list == NULL)
        return;

    SllNode *current = list->head;
    while (current != NULL)
    {
        SllNode *next = current->next;

        if (dataDestructor != NULL)
        {
            dataDestructor(current->data);
        }

        free(current);
        current = next;
    }

    free(list);
}

int sll_find(SllList *list, void *needle, int (*compare)(void *a, void *b), void **outResult)
{
    if (list == NULL)
        return 1;

    if (compare == NULL)
    {
        printf("Provide a compare function\n");
        return 1;
    }

    SllNode *current = list->head;
    while (current != NULL)
    {
        if (compare(current->data, needle) == 0)
        {
            *outResult = current->data;
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void sll_reverse(SllList *list)
{
    if (list == NULL)
    {
        return;
    }

    SllNode *current = list->head;
    SllNode *prev = NULL;

    while (current != NULL)
    {
        SllNode *next = current->next;

        current->next = prev;
        prev = current;
        current = next;
    }

    SllNode *tempHead = list->head;
    list->head = list->tail;
    list->tail = tempHead;
}
