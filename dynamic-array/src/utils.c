#include "../lib/utils.h"

// TODO Make some sort of a wrapper function around the switch(dataType) as its
//  used in castVoidToAType as welll and it might be used in other functions related
// to data types in the future
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
void printInt(const void *element)
{
    printf("%d ", *(int *)element);
}