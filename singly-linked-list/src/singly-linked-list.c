
#include <stdio.h>
#include <stdlib.h>
#include "../lib/singly-linked-list.h"

Node *singlyLinkedListCreate(size_t elementSize)
{
    Node *node = malloc(sizeof(Node));

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
    node->length = 0;

    return node;
}
void Insert(Node *node, void *dataOfNewNode)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Couldn't create a new node \n");
    }
}
