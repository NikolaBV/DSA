#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;
typedef struct
{
    Node *head;
    Node *tail;
    size_t length;
    size_t elementSize;
} DLinkedList;

DLinkedList *doublyLinkedListCreate(size_t elementSize);
void InsertAtTail(DLinkedList *linkedList, void *dataOfNewNode);
void InsertAtHead(DLinkedList *linkedList, void *dataOfNewNode);
void UpdateAtIndex(DLinkedList *list, void *newDataToInsertIntoNode, int index);
void InsertAtIndex(DLinkedList *list, void *data, int index);
void DeleteHead(DLinkedList *list);
void DeleteTail(DLinkedList *list);
//  void DeleteAtIndex(struct DLinkedList *list, int index);
//  void Traverse(struct DLinkedList *list, int (*callback)(void *data, void *context), void *context);
//  void reverse(struct DLinkedList *list);
//  void DLinkedListDestroy(struct DLinkedList *list, void (*dataDestructor)(void *data));
//  int find(struct DLinkedList *list, void *dataOfElementToFind, int(compare)(void *firstElement, void *secondElement), void **outResult);
//  struct Node *findNodeInListAtIndex(struct DLinkedList *list, int index);
