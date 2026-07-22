#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct DllNode
{
    void *data;
    struct DllNode *prev;
    struct DllNode *next;
} DllNode;

typedef struct
{
    DllNode *head;
    DllNode *tail;
    size_t length;
    size_t elementSize;
} DllList;

DllList *dll_create(size_t elementSize);

void dll_push_back(DllList *list, void *data);
void dll_push_front(DllList *list, void *data);
void dll_insert_at(DllList *list, void *data, int index);
void dll_set_at(DllList *list, void *data, int index);

void dll_pop_front(DllList *list);
void dll_pop_back(DllList *list);
void dll_destroy(DllList *list, void (*dataDestructor)(void *data));

bool dll_check_invariants(const DllList *list);

/* Still to implement:
void dll_remove_at(DllList *list, int index);
void dll_traverse(DllList *list, int (*callback)(void *data, void *context), void *context);
void dll_reverse(DllList *list);
int  dll_find(DllList *list, void *needle, int (*compare)(void *a, void *b), void **outResult);
void *dll_at(DllList *list, int index);
*/
