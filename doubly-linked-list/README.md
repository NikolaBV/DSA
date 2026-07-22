# Doubly linked list

In progress. Each node carries `prev` as well as `next`, which buys O(1)
movement backwards from any node — that is the only thing it buys, and it costs
8 bytes per node plus twice the pointer updates per operation.

Built from the repository root:

```bash
make test           # runs tests/test_dll.c
make demos && ./build/demo-dll
```

## Implemented

| Function | Notes |
|---|---|
| `dll_create(elementSize)` | |
| `dll_push_back` / `dll_push_front` | O(1) |
| `dll_insert_at(list, data, index)` | delegates to the push helpers at the ends |
| `dll_set_at(list, data, index)` | overwrites the pointer; the displaced payload is the caller's |
| `dll_pop_back` | **O(1)** via `tail->prev` |
| `dll_pop_front` | O(1) |
| `dll_check_invariants(list)` | test helper, see below |

## Still to implement

`dll_destroy`, `dll_remove_at`, `dll_traverse`, `dll_reverse`, `dll_find`,
`dll_at` — declared in a comment block at the bottom of the header.

Two of these should not be ports of the singly linked versions:

- **`dll_reverse`** — swap `prev`/`next` on each node, then swap `head`/`tail`.
  A different algorithm from the singly linked one, not a translation of it.
- **`dll_traverse`** — should take a direction, so the list can be walked from
  the tail. The singly linked list cannot do this at all.

A useful check when the set is finished: grep for `->prev`. If every occurrence
is an insert or delete *writing* it and none is a lookup *reading* it, the extra
pointer is being paid for and not used.

## `dll_check_invariants`

Walks forwards and backwards and verifies that

- the two directions agree on the node count, and that count equals `length`
- `head->prev == NULL` and `tail->next == NULL`
- `node->next->prev == node` for every node
- `head` and `tail` agree about whether the list is empty

It prints what failed and returns `false`. Call it after every mutation in
tests — it catches `prev`-wiring mistakes at the point they are made rather
than three operations later.

## Ownership warning

`dll_pop_front` and `dll_pop_back` call `free()` on the node's payload
unconditionally, which the singly linked list's equivalents do not do. Passing
a non-heap pointer (a stack address, or an integer cast to `void *`) and then
popping it is undefined behaviour. See the root README.
