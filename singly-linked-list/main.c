#include "lib/singly-linked-list.h"

int main()
{
    struct SLinkedList *linkedList = singlyLinkedListCreate(sizeof(int));
    if (linkedList == NULL)
    {
        free(linkedList);
        printf("Couldn't allocate memory for the new node");
        return -1;
    }

    InsertAtTail(linkedList, (void *)1);
    InsertAtTail(linkedList, (void *)2);

    InsertAtIndex(linkedList, (void *)50, 1);
    int *dataPtr = (int *)linkedList->head->next->next->data;
    printf("Value of node 1 is: %zu\n", dataPtr);

    free(linkedList);
}