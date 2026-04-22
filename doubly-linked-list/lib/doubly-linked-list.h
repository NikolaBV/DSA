#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
};

struct DLinkedList
{
    struct Node *head;
    struct Node *tail;
    size_t length;
    size_t elementSize;
};

struct DLinkedList *doublyLinkedListCreate(size_t elementSize);
// TODO
//  void InsertAtTail(struct DLinkedList *linkedList, void *dataOfNewNode);
//  void InsertAtHead(struct DLinkedList *linkedList, void *dataOfNewNode);
//  void UpdateAtIndex(struct DLinkedList *list, void *newDataToInsertIntoNode, int index);
//  void InsertAtIndex(struct DLinkedList *list, void *data, int index);
//  void DeleteAtIndex(struct DLinkedList *list, int index);
//  void DeleteHead(struct DLinkedList *list);
//  void DeleteTail(struct DLinkedList *list);
//  void Traverse(struct DLinkedList *list, int (*callback)(void *data, void *context), void *context);
//  void reverse(struct DLinkedList *list);
//  void DLinkedListDestroy(struct DLinkedList *list, void (*dataDestructor)(void *data));
//  int find(struct DLinkedList *list, void *dataOfElementToFind, int(compare)(void *firstElement, void *secondElement), void **outResult);
//  struct Node *findNodeInListAtIndex(struct DLinkedList *list, int index);
