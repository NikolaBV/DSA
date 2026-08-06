# Dynamic array

Contiguous storage that grows on insert and shrinks when it falls to a quarter
of capacity. Copies `elementSize` bytes per element and owns them, so callers
may pass stack values.

Built from the repository root:

```bash
make test           # runs tests/test_dynamic_array.c
make demos && ./build/demo-da
```

## API

| Function | Notes |
|---|---|
| `da_create(capacity, elementSize)` | |
| `da_destroy(array)` | tolerates `NULL` |
| `da_push_back(array, element)` | appends; doubles capacity when full |
| `da_remove_value(array, element)` | removes the first `memcmp` match, shifts the tail down |
| `da_at(array, index)` | returns a pointer into the buffer, `NULL` if out of range |
| `da_print(array)` | no-op unless `array->printer` is set |

## Known gaps

- `size` and `capacity` are `int` rather than `size_t`.
- `da_at` does not reject negative indices.
- Shrinking can drive `capacity` to 0, after which doubling stays at 0.
- No `da_insert_at` / `da_remove_at`.
