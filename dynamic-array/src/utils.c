#include "../lib/utils.h"

int sizeOfDataType(enum DATA_TYPE dataType)
{
    switch (dataType)
    {
    case INT:
        return sizeof(int);
    case FLOAT:
        return sizeof(float);

    case CHAR:
        return sizeof(char);

    default:
        return -1;
    }
}

int performArithmetic(enum ArithmeticOperation operation, int first, int second)
{
    switch (operation)
    {
    case ADD:
        return first + second;
    case MUL:
        return first * second;
    case DIV:
        return first / second;
    default:
        return first;
    }
}
void *castVoidToAType(void *voidValue, enum DATA_TYPE dataTypeToCastTo)
{
    switch (dataTypeToCastTo)
    {
    case INT:
        return (int *)voidValue;
    case FLOAT:
        return (float *)voidValue;

    case CHAR:
        return (char *)voidValue;

    default:
        return;
    }
}