#include "../doubly-linked-list/lib/doubly-linked-list.h"
#include "check.h"

/* dll_pop_front / dll_pop_back free the node's data, so every payload here is
   heap allocated. See the ownership note in the README. */

static int value_at(const DllList *list, size_t index)
{
    const DllNode *node = list->head;
    for (size_t i = 0; i < index; i++)
        node = node->next;
    return *(int *)node->data;
}

int main(void)
{
    DllList *list = dll_create(sizeof(int));
    CHECK(list != NULL);
    CHECK(list->head == NULL && list->tail == NULL);
    CHECK(list->length == 0);
    CHECK(dll_check_invariants(list));

    /* push_back */
    dll_push_back(list, heap_int(1));
    CHECK(dll_check_invariants(list));
    CHECK(list->head == list->tail);
    CHECK(list->head->next == NULL && list->head->prev == NULL);

    dll_push_back(list, heap_int(2));
    dll_push_back(list, heap_int(3));
    CHECK(dll_check_invariants(list));
    CHECK(list->length == 3);
    CHECK(value_at(list, 0) == 1 && value_at(list, 1) == 2 && value_at(list, 2) == 3);
    CHECK(*(int *)list->tail->data == 3);

    /* push_front */
    dll_push_front(list, heap_int(0));
    CHECK(dll_check_invariants(list));
    CHECK(list->length == 4);
    CHECK(value_at(list, 0) == 0);
    CHECK(*(int *)list->head->data == 0);

    /* insert_at, middle -- the case that used to silently do nothing */
    dll_insert_at(list, heap_int(1000), 2);
    CHECK(dll_check_invariants(list));
    CHECK(list->length == 5);
    CHECK(value_at(list, 0) == 0);
    CHECK(value_at(list, 1) == 1);
    CHECK(value_at(list, 2) == 1000);
    CHECK(value_at(list, 3) == 2);
    CHECK(value_at(list, 4) == 3);

    /* insert_at, index 0 and index == length delegate to the push helpers */
    dll_insert_at(list, heap_int(7), 0);
    CHECK(dll_check_invariants(list));
    CHECK(value_at(list, 0) == 7);

    dll_insert_at(list, heap_int(9), (int)list->length);
    CHECK(dll_check_invariants(list));
    CHECK(*(int *)list->tail->data == 9);
    CHECK(list->length == 7);

    /* out of bounds must not mutate the list. The rejected payload stays the
       caller's problem -- dll_insert_at never took ownership of it. */
    size_t before = list->length;
    int *rejected = heap_int(-1);
    dll_insert_at(list, rejected, 999);
    dll_insert_at(list, rejected, -1);
    CHECK(list->length == before);
    CHECK(dll_check_invariants(list));
    free(rejected);

    /* set_at overwrites the pointer at that index and does NOT free what was
       there, so the caller has to hold on to it. */
    void *displaced = list->head->next->data;
    dll_set_at(list, heap_int(555), 1);
    free(displaced);
    CHECK(dll_check_invariants(list));
    CHECK(value_at(list, 1) == 555);
    CHECK(list->length == before);

    /* pop_back is the O(1) path via tail->prev */
    dll_pop_back(list);
    CHECK(dll_check_invariants(list));
    CHECK(list->length == before - 1);
    CHECK(*(int *)list->tail->data == 3);

    /* pop_front */
    dll_pop_front(list);
    CHECK(dll_check_invariants(list));
    CHECK(list->length == before - 2);
    CHECK(list->head->prev == NULL);

    /* drain the list completely */
    while (list->length > 0)
    {
        dll_pop_back(list);
        CHECK(dll_check_invariants(list));
    }
    CHECK(list->head == NULL && list->tail == NULL);

    /* popping an empty list is a no-op, not a crash */
    dll_pop_back(list);
    dll_pop_front(list);
    CHECK(list->length == 0);
    CHECK(dll_check_invariants(list));

    free(list);
    TEST_DONE();
}
