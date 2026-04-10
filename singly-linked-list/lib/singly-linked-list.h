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
struct Node *findNodeInListAtIndex(struct SLinkedList *list, int index);
// 3. Deletion from the beginning
// 4. Deletion from the end
// 5. Deletion at the position
// 6. Traversal
// 7. Reverse
// 8. Search
