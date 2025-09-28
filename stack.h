#include <stdio.h>
#include <stddef.h>

#define POIZON 765418

#define ASSERTS(stk) \
    assert(stk != NULL);\
    assert(stk->size >= 0);\
    assert(stk->capacity > 0);\
    assert(stk->data != NULL);


typedef int USED_TYPE;

enum StackErr_t {
    NO_ERROR = 0,
    ERROR_IN_SIZE,
    ERROR_IN_CAPACITY,
    ERROR_IN_DATA, //ошибка в целостности данных для хэш функции
};

struct stack_t
{
    USED_TYPE *data;
    ssize_t size;
    ssize_t capacity; //переменная для хранения суммы чисел в стеке
};

StackErr_t StackInit(struct stack_t *stk, ssize_t capacity);
StackErr_t StackPush(struct stack_t *stk, USED_TYPE value);
USED_TYPE StackPop(struct stack_t *stk, StackErr_t *err);
StackErr_t StackDestroy(struct stack_t *stk);
StackErr_t StackVerify(struct stack_t *stk);
void StackDump(struct stack_t *stk, const char *file, int line);
