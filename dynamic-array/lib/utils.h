#include <stdio.h>
typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV
} arithmeticOperation;

// TODO Think about either removing this or making it generic
int performArithmetic(arithmeticOperation operation, int first, int second);
void printInt(const void *element);