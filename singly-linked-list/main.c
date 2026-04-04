#include "lib/singly-linked-list.h"

int main()
{
    struct Node *node = singlyLinkedListCreate(sizeof(int));
    InsertAtTail(node, (void *)1);

    int *dataPtr = (int *)node->next->next->next->data;
    printf("%zu \n", dataPtr);

    free(node->data);
    free(node);
}