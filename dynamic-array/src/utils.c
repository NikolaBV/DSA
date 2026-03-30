#include "../lib/utils.h"

int performArithmetic(arithmeticOperation operation, int first, int second)
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