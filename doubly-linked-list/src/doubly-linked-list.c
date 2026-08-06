#include "dsa/doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

static DllNode *dll_node_at(DllList *list, int index)
{
    if (index < 0 || (size_t)index >= list->length)
    {
        return NULL;
    }

    DllNode *node = list->head;
    for (int i = 0; i < index; i++)
    {
        node = node->next;
    }
    return node;
}

DllList *dll_create(size_t elementSize)
{
    DllList *linkedList = malloc(sizeof(DllList));

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

void dll_push_back(DllList *linkedList, void *dataOfNewNode)
{
    DllNode *newNode = malloc(sizeof(DllNode));

    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for the new node\n");
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

void dll_push_front(DllList *linkedList, void *dataOfNewNode)
{
    DllNode *newNode = malloc(sizeof(DllNode));

    if (newNode == NULL)
    {
        printf("Couldn't allocate space for a node\n");
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
        DllNode *prevHead = linkedList->head;
        linkedList->head = newNode;
        linkedList->head->next = prevHead;
        linkedList->head->next->prev = linkedList->head;
    }
    linkedList->length++;
}

void dll_set_at(DllList *list, void *newDataToInsertIntoNode, int index)
{
    if (list->head == NULL)
    {
        printf("Can't insert at index of an empty linked list\n");
        return;
    }

    DllNode *elementAtIndex = dll_node_at(list, index);

    if (elementAtIndex == NULL)
    {
        printf("Index out of bounds\n");
        return;
    }

    elementAtIndex->data = newDataToInsertIntoNode;
}

void dll_insert_at(DllList *list, void *data, int index)
{
    if (index < 0 || (size_t)index > list->length)
    {
        printf("Index out of bounds\n");
        return;
    }

    if (index == 0)
    {
        dll_push_front(list, data);
        return;
    }

    if ((size_t)index == list->length)
    {
        dll_push_back(list, data);
        return;
    }

    DllNode *newNode = malloc(sizeof(DllNode));

    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for the new node\n");
        return;
    }

    newNode->data = data;

    DllNode *elementAtTheIndex = dll_node_at(list, index);
    newNode->next = elementAtTheIndex;
    newNode->prev = elementAtTheIndex->prev;
    elementAtTheIndex->prev->next = newNode;
    elementAtTheIndex->prev = newNode;
    list->length++;
}

void dll_pop_back(DllList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete: List is empty.\n");
        return;
    }

    DllNode *oldTail = list->tail;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        DllNode *newTail = oldTail->prev;
        list->tail = newTail;
        list->tail->next = NULL;
    }

    free(oldTail->data);
    free(oldTail);
    list->length--;
}

void dll_pop_front(DllList *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete head: List is empty.\n");
        return;
    }

    DllNode *oldHead = list->head;
    list->head = oldHead->next;

    if (list->length > 1)
    {
        list->head->prev = NULL;
    }
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    list->length--;

    free(oldHead->data);
    free(oldHead);
}

void dll_destroy(DllList *list, void (*dataDestructor)(void *data))
{
    if (list == NULL)
        return;

    DllNode *current = list->head;
    while (current != NULL)
    {
        DllNode *next = current->next;

        if (dataDestructor != NULL)
        {
            dataDestructor(current->data);
        }

        free(current);
        current = next;
    }

    free(list);
}

void dll_remove_at(DllList *list, int index)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Can't delete: List is empty.\n");
        return;
    }
    if (index == 0)
    {
        dll_pop_front(list);
        return;
    }
    if ((size_t)index == list->length - 1)
    {
        dll_pop_back(list);

        return;
    }

    if (index < 0 || index > (int)list->length - 1)
    {
        printf("Index out of bounds\n");
        return;
    }
    DllNode *nodeToRemove = dll_node_at(list, index);

    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;
    free(nodeToRemove->data);
    free(nodeToRemove);
    list->length--;
}

void dll_traverse(DllList *list, int (*callback)(void *data, void *context), void *context)
{
    if (list == NULL)
        return;
    DllNode *currentNode = list->head;

    while (currentNode != NULL)
    {
        DllNode *nextNode = currentNode->next;

        if (callback(currentNode->data, context))
            break;

        currentNode = nextNode;
    }
}

void dll_reverse(DllList *list)
{
    if (list == NULL)
    {
        return;
    }

    DllNode *current = list->head;
    while (current != NULL)
    {
        DllNode *next = current->next;

        current->next = current->prev;
        current->prev = next;
        current = next;
    }

    DllNode *tempHead = list->head;
    list->head = list->tail;
    list->tail = tempHead;
}

int dll_find(DllList *list, void *needle, int (*compare)(void *a, void *b), void **outResult)
{
    if (list == NULL || compare == NULL)
        return 1;

    DllNode *current = list->head;
    while (current != NULL)
    {
        if (compare(current->data, needle) == 0)
        {
            if (outResult != NULL)
                *outResult = current->data;
            return 0;
        }
        current = current->next;
    }

    if (outResult != NULL)
        *outResult = NULL;

    return 1;
}

bool dll_check_invariants(const DllList *list)
{
    if (list == NULL)
    {
        printf("INVARIANT: list is NULL\n");
        return false;
    }

    if ((list->head == NULL) != (list->tail == NULL))
    {
        printf("INVARIANT: head and tail disagree about emptiness\n");
        return false;
    }

    if (list->head != NULL && list->head->prev != NULL)
    {
        printf("INVARIANT: head->prev is not NULL\n");
        return false;
    }

    if (list->tail != NULL && list->tail->next != NULL)
    {
        printf("INVARIANT: tail->next is not NULL\n");
        return false;
    }

    size_t forward = 0;
    DllNode *previous = NULL;
    for (DllNode *node = list->head; node != NULL; node = node->next)
    {
        if (node->prev != previous)
        {
            printf("INVARIANT: forward walk, node %zu has a wrong prev pointer\n", forward);
            return false;
        }
        previous = node;
        forward++;
    }

    if (previous != list->tail)
    {
        printf("INVARIANT: forward walk did not end at tail\n");
        return false;
    }

    size_t backward = 0;
    DllNode *following = NULL;
    for (DllNode *node = list->tail; node != NULL; node = node->prev)
    {
        if (node->next != following)
        {
            printf("INVARIANT: backward walk, node %zu has a wrong next pointer\n", backward);
            return false;
        }
        following = node;
        backward++;
    }

    if (following != list->head)
    {
        printf("INVARIANT: backward walk did not end at head\n");
        return false;
    }

    if (forward != backward)
    {
        printf("INVARIANT: forward count %zu != backward count %zu\n", forward, backward);
        return false;
    }

    if (forward != list->length)
    {
        printf("INVARIANT: walked %zu nodes but length says %zu\n", forward, list->length);
        return false;
    }

    return true;
}
