#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    struct Node *next;
    void *data;
    int length;
    size_t elementSize;
} Node;

// TODO Implement all functions
Node *singlyLinkedListCreate(size_t elementSize);
void Insert(Node *node, void *dataOfNewNode);
// 1. Insertion at the beginning
// 2. Insertion At the end
// 3. Insertion at the position
// 4. Deletion from the beginning
// 5. Deletion from the end
// 6. Deletion at the position
// 7. Traversal
// 8. Reverse
// 9. Search
