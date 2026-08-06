# libdsa

Hand-written data structures in C, built as fundamentals practice.

| Structure | Status |
|---|---|
| Dynamic array | implemented |
| Singly linked list | implemented |
| Doubly linked list | in progress — see `include/dsa/doubly_linked_list.h` |
| Stack | not started |
| Queue | not started |

## Building

```bash
make              # build/libdsa.a
make test         # build and run every test binary
make asan         # same, under AddressSanitizer + UBSan
make valgrind     # same, under valgrind --leak-check=full
make link-check   # link all structures into one binary
make demos        # build the per-project demo programs
make clean
```

Everything compiles with `-std=c11 -Wall -Wextra -Werror -g`. A warning is a
build failure.

The sanitizer targets need the runtime libraries:

```bash
sudo dnf install libasan libubsan
```

## Tests

`tests/check.h` provides a `CHECK(cond)` macro that prints `FAIL file:line: expr`
and exits non-zero. Each test file is a standalone binary with its own `main()`
— there is no framework and no registration.

The doubly linked list additionally exposes `dll_check_invariants()`, which
walks the list forwards and backwards and verifies that the two directions
agree on the node count, that `head->prev` and `tail->next` are `NULL`, and
that `node->next->prev == node` throughout. Call it after every mutation.

## Naming

`snake_case`, prefixed per structure: `da_`, `sll_`, `dll_`. C has no
namespaces, so without the prefixes the two lists both defined `InsertAtTail`,
`InsertAtHead`, `UpdateAtIndex`, `find` and `struct Node` at global scope and
could not be linked into the same binary. `make link-check` is the regression
test for that.

## Ownership — currently inconsistent

**This is the open design question, not a settled convention.**

- **Dynamic array**: copies `elementSize` bytes on insert and owns them.
  `da_destroy` frees the buffer. Callers can pass stack values.
- **Both lists**: store the caller's `void *` and ignore `elementSize`
  entirely. Callers must supply a pointer that outlives the list.

Within the lists it is inconsistent again:

| Function | Frees the payload? |
|---|---|
| `sll_pop_front` / `sll_pop_back` / `sll_remove_at` | no |
| `sll_destroy` | only via the `dataDestructor` callback |
| `dll_pop_front` / `dll_pop_back` | **yes, unconditionally** |
| `sll_set_at` / `dll_set_at` | no — the displaced pointer leaks unless the caller kept it |

So a payload handed to the doubly linked list must be `malloc`'d and must not
be freed by the caller, while the same payload handed to the singly linked list
must be freed by the caller. The tests document this by allocating every list
payload on the heap and freeing explicitly where the list does not.

Resolving this — pick copy semantics or borrow semantics and apply it
everywhere — is the next piece of work.
