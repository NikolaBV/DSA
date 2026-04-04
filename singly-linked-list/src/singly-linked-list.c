
#include <stdio.h>
#include <stdlib.h>
#include "../lib/singly-linked-list.h"

struct Node *singlyLinkedListCreate(size_t elementSize)
{
    struct Node *node = malloc(sizeof(struct Node));

    if (node == NULL)
    {
        printf("Couldn't create a linked list \n");
        return NULL;
    }
    void *temp = malloc(elementSize);

    if (temp == NULL)
    {
        free(node);
        printf("Couldn't create a linked list \n");
        return NULL;
    }

    node->data = temp;
    node->elementSize = elementSize;
    node->next = NULL;

    return node;
}

struct Node *findLastNode(struct Node *node)
{
    if (node->next == NULL)
    {
        return node;
    }
    findLastNode(node->next);
}

void InsertAtTail(struct Node *node, void *dataOfNewNode)
{
    struct Node *lastNode = findLastNode(node);
    if (lastNode == NULL)
    {
        printf("Couldn't find the last node\n");
        return;
    }
    struct Node *newNode = malloc(sizeof(node));

    if (newNode == NULL)
    {
        printf("Couldn't allocate memory for a new node\n");
        return;
    }

    newNode->data = dataOfNewNode;
    newNode->elementSize = node->elementSize;
    newNode->next = NULL;

    lastNode->next = newNode;
}
