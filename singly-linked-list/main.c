#include "lib/singly-linked-list.h"

int main()
{
    Node *node = singlyLinkedListCreate(sizeof(int));
    int *dataPtr = (int *)node->data;

    printf("Element size: %zu, Value: %d\n", node->elementSize, *dataPtr);

    free(node->data);
    free(node);
}