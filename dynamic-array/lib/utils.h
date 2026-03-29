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

struct DynamicArray
{
    void *data;
    int size;
    int capacity;
    enum DATA_TYPE dataType;
};

int performArithmetic(enum ArithmeticOperation operation, int first, int second);
int sizeOfDataType(enum DATA_TYPE dataType);
void *castVoidToAType(void *voidValue, enum DATA_TYPE dataTypeToCastTo);