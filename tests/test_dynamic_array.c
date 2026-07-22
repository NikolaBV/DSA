#include "../dynamic-array/lib/dynamic_array.h"
#include "check.h"

#include <string.h>

/* Unlike the two lists, the dynamic array copies elementSize bytes and owns
   them, so values here are plain stack ints. */

static int printed = 0;

static void count_printer(const void *element)
{
    (void)element;
    printed++;
}

int main(void)
{
    DynamicArray *array = da_create(2, sizeof(int));
    CHECK(array != NULL);
    CHECK(array->size == 0);
    CHECK(array->capacity == 2);
    CHECK(array->data != NULL);

    /* push_back appends and grows capacity when full */
    for (int i = 0; i < 5; i++)
    {
        da_push_back(array, &i);
        CHECK(array->size == i + 1);
    }
    CHECK(array->capacity >= 5);

    for (int i = 0; i < 5; i++)
    {
        CHECK(*(int *)da_at(array, i) == i);
    }

    /* the array copies its input -- mutating the source must not change it */
    int source = 42;
    da_push_back(array, &source);
    source = 99;
    CHECK(*(int *)da_at(array, 5) == 42);
    CHECK(array->size == 6);

    /* reading past the end returns NULL rather than walking off the buffer */
    CHECK(da_at(array, array->size) == NULL);
    CHECK(da_at(array, 12345) == NULL);

    /* remove_value removes the first match and shifts the rest down */
    int target = 2;
    da_remove_value(array, &target);
    CHECK(array->size == 5);
    CHECK(*(int *)da_at(array, 0) == 0);
    CHECK(*(int *)da_at(array, 1) == 1);
    CHECK(*(int *)da_at(array, 2) == 3);
    CHECK(*(int *)da_at(array, 3) == 4);
    CHECK(*(int *)da_at(array, 4) == 42);

    /* removing something that is not there leaves the array untouched */
    int absent = 777;
    int sizeBefore = array->size;
    da_remove_value(array, &absent);
    CHECK(array->size == sizeBefore);

    /* the printer callback is invoked once per element */
    array->printer = count_printer;
    printed = 0;
    da_print(array);
    CHECK(printed == array->size);

    da_destroy(array);

    /* da_destroy tolerates NULL */
    da_destroy(NULL);

    TEST_DONE();
}
