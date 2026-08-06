#include "dsa/doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static int *heap_int(int value)
{
    int *p = malloc(sizeof(int));
    *p = value;
    return p;
}

static int compareInts(void *firstNumber, void *secondNumber)
{
    return *(int *)firstNumber - *(int *)secondNumber;
}

static void print_forwards(const DllList *list)
{
    printf("head -> ");
    for (const DllNode *n = list->head; n != NULL; n = n->next)
        printf("%d -> ", *(int *)n->data);
    printf("tail\n");
}

static void print_backwards(const DllList *list)
{
    printf("tail -> ");
    for (const DllNode *n = list->tail; n != NULL; n = n->prev)
        printf("%d -> ", *(int *)n->data);
    printf("head\n");
}

int main(void)
{
    DllList *linkedList = dll_create(sizeof(int));
    if (linkedList == NULL)
        return 1;

    dll_push_back(linkedList, heap_int(1));
    dll_push_back(linkedList, heap_int(2));
    dll_push_back(linkedList, heap_int(3));
    dll_insert_at(linkedList, heap_int(1000), 1);

    print_forwards(linkedList);
    print_backwards(linkedList);
    printf("invariants hold: %s\n", dll_check_invariants(linkedList) ? "yes" : "no");

    dll_pop_back(linkedList);
    dll_pop_front(linkedList);
    printf("after popping both ends:\n");
    print_forwards(linkedList);

    while (linkedList->length > 0)
        dll_pop_back(linkedList);
    dll_destroy(linkedList, free);
    return 0;
}
