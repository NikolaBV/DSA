#include "../lib/doubly-linked-list.h"

struct Node *findNodeInListAtIndex(DLinkedList *list, int index)
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
    Node *newNode = malloc(sizeof(Node));

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
        Node *prevHead = linkedList->head;
        linkedList->head = newNode;
        linkedList->head->next = prevHead;
        linkedList->head->next->prev = linkedList->head;
    }
    linkedList->length++;
}

void UpdateAtIndex(DLinkedList *list, void *newDataToInsertIntoNode, int index)
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

void InsertAtIndex(DLinkedList *list, void *data, int index)
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

    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;

    Node *elementAtTheIndex = findNodeInListAtIndex(list, index);
    newNode->next = elementAtTheIndex;
    newNode->prev = elementAtTheIndex->prev;
    elementAtTheIndex->prev->next = newNode;
    elementAtTheIndex->prev = newNode;
    list->length++;
}