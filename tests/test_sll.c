#include "../singly-linked-list/lib/singly-linked-list.h"
#include "check.h"

static int value_at(const SllList *list, size_t index)
{
    const SllNode *node = list->head;
    for (size_t i = 0; i < index; i++)
        node = node->next;
    return *(int *)node->data;
}

static int sum_callback(void *data, void *context)
{
    *(int *)context += *(int *)data;
    return 0;
}

static int stop_after_first(void *data, void *context)
{
    (void)data;
    *(int *)context += 1;
    return 1; /* non-zero means stop */
}

static int compare_ints(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

int main(void)
{
    /* Regression: push_front into an EMPTY list used to leave newNode->next
       uninitialized. It read as NULL only because fresh pages are zeroed;
       valgrind reported "conditional jump depends on uninitialised value". */
    {
        SllList *list = sll_create(sizeof(int));
        sll_push_front(list, heap_int(1));
        CHECK(list->head->next == NULL);
        CHECK(list->head == list->tail);
        CHECK(list->length == 1);
        sll_destroy(list, free);
    }

    SllList *list = sll_create(sizeof(int));
    CHECK(list != NULL);
    CHECK(list->head == NULL && list->tail == NULL && list->length == 0);

    /* push_back / push_front ordering */
    sll_push_back(list, heap_int(1));
    sll_push_back(list, heap_int(2));
    sll_push_back(list, heap_int(3));
    CHECK(list->length == 3);
    CHECK(value_at(list, 0) == 1 && value_at(list, 2) == 3);
    CHECK(*(int *)list->tail->data == 3);
    CHECK(list->tail->next == NULL);

    sll_push_front(list, heap_int(0));
    CHECK(list->length == 4);
    CHECK(value_at(list, 0) == 0);

    /* insert_at: middle, head, tail */
    sll_insert_at(list, heap_int(1000), 2);
    CHECK(list->length == 5);
    CHECK(value_at(list, 1) == 1 && value_at(list, 2) == 1000 && value_at(list, 3) == 2);

    sll_insert_at(list, heap_int(7), 0);
    CHECK(value_at(list, 0) == 7);

    sll_insert_at(list, heap_int(9), (int)list->length);
    CHECK(*(int *)list->tail->data == 9);
    CHECK(list->tail->next == NULL);
    CHECK(list->length == 7);

    /* out of bounds is a no-op. The rejected payload stays the caller's
       problem -- sll_insert_at never took ownership of it. */
    size_t before = list->length;
    int *rejected = heap_int(-1);
    sll_insert_at(list, rejected, 999);
    sll_insert_at(list, rejected, -1);
    CHECK(list->length == before);
    free(rejected);

    /* set_at */
    int *replaced = list->head->next->data;
    sll_set_at(list, heap_int(555), 1);
    CHECK(value_at(list, 1) == 555);
    free(replaced);

    /* the list is now [7, 555, 1, 1000, 2, 3, 9] */
    CHECK(value_at(list, 0) == 7 && value_at(list, 1) == 555 && value_at(list, 2) == 1);
    CHECK(value_at(list, 3) == 1000 && value_at(list, 6) == 9);

    /* traverse must hand the callback the DATA, not the node */
    int total = 0;
    sll_traverse(list, sum_callback, &total);
    CHECK(total == 7 + 555 + 1 + 1000 + 2 + 3 + 9);

    /* a non-zero return stops the walk */
    int visits = 0;
    sll_traverse(list, stop_after_first, &visits);
    CHECK(visits == 1);

    /* find */
    int needle = 1000;
    void *found = NULL;
    CHECK(sll_find(list, &needle, compare_ints, &found) == 0);
    CHECK(found != NULL && *(int *)found == 1000);

    int missing = 123456;
    found = NULL;
    CHECK(sll_find(list, &missing, compare_ints, &found) == 1);
    CHECK(found == NULL);

    /* reverse swaps head and tail and the whole ordering */
    int firstBefore = value_at(list, 0);
    int lastBefore = *(int *)list->tail->data;
    sll_reverse(list);
    CHECK(value_at(list, 0) == lastBefore);
    CHECK(*(int *)list->tail->data == firstBefore);
    CHECK(list->tail->next == NULL);
    CHECK(list->length == before);

    /* the pop helpers free the node but not the payload, so the caller
       still owns the data pointer -- grab it before popping */
    void *headData = list->head->data;
    sll_pop_front(list);
    free(headData);
    CHECK(list->length == before - 1);

    void *tailData = list->tail->data;
    sll_pop_back(list);
    free(tailData);
    CHECK(list->length == before - 2);
    CHECK(list->tail->next == NULL);

    void *midData = list->head->next->data;
    sll_remove_at(list, 1);
    free(midData);
    CHECK(list->length == before - 3);

    /* drain, then confirm empty pops are no-ops */
    while (list->length > 0)
    {
        void *d = list->head->data;
        sll_pop_front(list);
        free(d);
    }
    CHECK(list->head == NULL && list->tail == NULL);
    sll_pop_front(list);
    sll_pop_back(list);
    CHECK(list->length == 0);

    sll_destroy(list, free);
    TEST_DONE();
}
