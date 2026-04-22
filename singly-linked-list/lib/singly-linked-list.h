#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    struct Node *next;
};

struct SLinkedList
{
    struct Node *head;
    struct Node *tail;
    size_t length;
    size_t elementSize;
};

struct SLinkedList *singlyLinkedListCreate(size_t elementSize);
void InsertAtTail(struct SLinkedList *linkedList, void *dataOfNewNode);
void InsertAtHead(struct SLinkedList *linkedList, void *dataOfNewNode);
void UpdateAtIndex(struct SLinkedList *list, void *newDataToInsertIntoNode, int index);
void InsertAtIndex(struct SLinkedList *list, void *data, int index);
void DeleteAtIndex(struct SLinkedList *list, int index);
void DeleteHead(struct SLinkedList *list);
void DeleteTail(struct SLinkedList *list);
void Traverse(struct SLinkedList *list, int (*callback)(void *data, void *context), void *context);
void reverse(struct SLinkedList *list);
void SLinkedListDestroy(struct SLinkedList *list, void (*dataDestructor)(void *data));
int find(struct SLinkedList *list, void *dataOfElementToFind, int(compare)(void *firstElement, void *secondElement), void **outResult);
struct Node *findNodeInListAtIndex(struct SLinkedList *list, int index);
// 6.1. When you implement a traversal function, implement these as callbacks to the traversal:
// 6.2 Reverse
