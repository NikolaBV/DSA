/* Links all three structures into a single binary.

   Before the symbols were prefixed this could not compile OR link: every
   project declared its own `struct Node`, and the two lists both defined
   InsertAtTail, InsertAtHead, UpdateAtIndex and find at global scope. */

#include "../doubly-linked-list/lib/doubly-linked-list.h"
#include "../dynamic-array/lib/dynamic_array.h"
#include "../singly-linked-list/lib/singly-linked-list.h"
#include "check.h"

int main(void)
{
    DynamicArray *array = da_create(4, sizeof(int));
    SllList *sll = sll_create(sizeof(int));
    DllList *dll = dll_create(sizeof(int));

    CHECK(array != NULL && sll != NULL && dll != NULL);

    int value = 1;
    da_push_back(array, &value);
    sll_push_back(sll, heap_int(2));
    dll_push_back(dll, heap_int(3));

    CHECK(*(int *)da_at(array, 0) == 1);
    CHECK(*(int *)sll->head->data == 2);
    CHECK(*(int *)dll->head->data == 3);
    CHECK(dll_check_invariants(dll));

    /* The three Node types are distinct types now, not one colliding one. */
    CHECK(sizeof(SllNode) != sizeof(DllNode));

    dll_pop_back(dll);
    free(dll);
    sll_destroy(sll, free);
    da_destroy(array);

    TEST_DONE();
}
