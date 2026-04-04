#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    int elementSize;
    struct Node *next;
};

// TODO Implement all functions
struct Node *singlyLinkedListCreate(size_t elementSize);
void InsertAtHead(struct Node *node, void *dataOfNewNode);
void InsertAtTail(struct Node *node, void *dataOfNewNode);
struct Node *findLastNode(struct Node *node);
// 1. Insertion at the beginning
// 2. Insertion At the end
// 3. Insertion at the position
// 4. Deletion from the beginning
// 5. Deletion from the end
// 6. Deletion at the position
// 7. Traversal
// 8. Reverse
// 9. Search
