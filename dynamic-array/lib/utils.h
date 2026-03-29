#include <stdio.h>
enum ArithmeticOperation
{
    ADD,
    SUB,
    MUL,
    DIV
};
enum DATA_TYPE
{
    INT,
    FLOAT,
    CHAR,
};

int performArithmetic(enum ArithmeticOperation operation, int first, int second);
int sizeOfDataType(enum DATA_TYPE dataType);
void printInt(const void *element);