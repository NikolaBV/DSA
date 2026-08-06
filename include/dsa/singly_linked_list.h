#pragma once

#include <stddef.h>

typedef struct SllNode
{
    void *data;
    struct SllNode *next;
} SllNode;

typedef struct
{
    SllNode *head;
    SllNode *tail;
    size_t length;
    size_t elementSize;
} SllList;

SllList *sll_create(size_t elementSize);
void sll_destroy(SllList *list, void (*dataDestructor)(void *data));

void sll_push_back(SllList *list, void *data);
void sll_push_front(SllList *list, void *data);
void sll_insert_at(SllList *list, void *data, int index);
void sll_set_at(SllList *list, void *data, int index);

void sll_pop_front(SllList *list);
void sll_pop_back(SllList *list);
void sll_remove_at(SllList *list, int index);

void sll_traverse(SllList *list, int (*callback)(void *data, void *context), void *context);
int sll_find(SllList *list, void *needle, int (*compare)(void *a, void *b), void **outResult);
void sll_reverse(SllList *list);
