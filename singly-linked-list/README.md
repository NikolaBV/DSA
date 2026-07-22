# Singly linked list

Stores the caller's `void *` per node; `elementSize` is recorded but unused.
The payload must outlive the list. See the ownership section in the root
README — the pop functions here do *not* free payloads, unlike the doubly
linked list's.

Built from the repository root:

```bash
make test           # runs tests/test_sll.c
make demos && ./build/demo-sll
```

## API

| Function | Notes |
|---|---|
| `sll_create(elementSize)` / `sll_destroy(list, dataDestructor)` | pass `free` as the destructor for heap payloads, or `NULL` |
| `sll_push_back` / `sll_push_front` | O(1) — `tail` is tracked |
| `sll_insert_at(list, data, index)` | delegates to the push helpers at the ends |
| `sll_set_at(list, data, index)` | overwrites the pointer; the displaced payload is the caller's |
| `sll_pop_front` | O(1) |
| `sll_pop_back` | **O(n)** — see below |
| `sll_remove_at(list, index)` | |
| `sll_traverse(list, callback, context)` | the callback receives the *data*, not the node; return non-zero to stop |
| `sll_find(list, needle, compare, outResult)` | returns 0 on a hit |
| `sll_reverse(list)` | |

## Why `sll_pop_back` is O(n)

There is no way back from the tail, so finding the new tail costs a full walk.
The doubly linked list does the same thing in O(1) with `tail->prev`. That
single difference is the reason the doubly linked list exists.

## Fixed here

`sll_push_front` used to leave `newNode->next` uninitialized when inserting
into an empty list. It read as `NULL` only because freshly mapped pages are
zeroed; valgrind reported *"conditional jump depends on uninitialised value"*.
`tests/test_sll.c` opens with the regression test.
