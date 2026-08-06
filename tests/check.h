#pragma once

#include <stdio.h>
#include <stdlib.h>

/* Minimal assertion harness. Each test file is its own binary with its own
   main(), so there is no registration or framework -- CHECK either passes or
   kills the process with a file:line. */

static int checks_run = 0;

#define CHECK(cond)                                                          \
    do                                                                       \
    {                                                                        \
        checks_run++;                                                        \
        if (!(cond))                                                         \
        {                                                                    \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);  \
            exit(1);                                                         \
        }                                                                    \
    } while (0)

#define TEST_DONE()                                                          \
    do                                                                       \
    {                                                                        \
        printf("PASS %s (%d checks)\n", __FILE__, checks_run);               \
        return 0;                                                            \
    } while (0)

/* Both list implementations store a caller-supplied pointer rather than
   copying elementSize bytes, so tests allocate their payloads on the heap. */
static inline int *heap_int(int value)
{
    int *p = malloc(sizeof(int));
    if (p == NULL)
        exit(1);
    *p = value;
    return p;
}
