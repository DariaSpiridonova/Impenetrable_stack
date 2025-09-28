#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

StackErr_t StackInit(struct stack_t *stk, ssize_t capacity)
{
    assert(stk != NULL);
    assert(capacity > 0);

    stk->data = (USED_TYPE *)calloc((size_t)capacity + 2, sizeof(USED_TYPE));
    // сделать тут канарейку и потом её двигать при необходимости

    for (ssize_t i = 0; i < capacity; i++)
    {
        stk->data[i] = POIZON;
    }

    StackErr_t err = NO_ERROR;
    if ((err = StackVerify(stk)))
    {
        StackDump(stk,__FILE__, __LINE__); // можешь впихнуть в stackverify
        return err;
    }

    return err;
}

StackErr_t StackPush(struct stack_t *stk, USED_TYPE value)
{
    ASSERTS(stk);

    StackErr_t err = NO_ERROR;
    if (err)
    {
        StackDump(stk,__FILE__, __LINE__);
        return err;
    }

    stk->data[stk->size++] = value;

    if (stk->size >= stk->capacity)
    {
        printf("MORE\n");
        stk->data = (USED_TYPE *)realloc(stk->data, 2*(size_t)(stk->capacity)*sizeof(USED_TYPE));
        stk->capacity *= 2;
    }
    
    for (ssize_t j = stk->size; j < stk->capacity; j++)
    {
        stk->data[j] = POIZON;
    }

    err = NO_ERROR;
    if (err)
    {
        StackDump(stk,__FILE__, __LINE__);
        return err;
    }

    ASSERTS(stk);

    return err;
}

USED_TYPE StackPop(struct stack_t *stk, StackErr_t *err)
{
    ASSERTS(stk);

    *err = StackVerify(stk);
    if (*err) return POIZON;

    USED_TYPE value_from_stack = stk->data[--stk->size];

    if (stk->size < 0) stk->size = 0;

    *err = StackVerify(stk);
    if (*err) return POIZON;

    return value_from_stack;
}

StackErr_t StackDestroy(struct stack_t *stk)
{
    ASSERTS(stk);

    StackErr_t err = NO_ERROR;
    if (err)
    {
        StackDump(stk,__FILE__, __LINE__);
        return err;
    }

    free(stk->data);

    return err;
}

StackErr_t StackVerify(struct stack_t *stk)
{
    ASSERTS(stk);

    if (stk->size < 0) return ERROR_IN_SIZE;
    else if (stk->capacity <= 0) return ERROR_IN_CAPACITY;
    else if (stk->data == NULL) return ERROR_IN_DATA;
    return NO_ERROR;
}

void StackDump(struct stack_t *stk, const char *file, int line)
{
    printf("StackDump called from %s :%d\n", file, line);
    printf("Stack[%p]\n", &stk);
    printf("{\n");
    printf("    size = %ld\n", stk->size);
    printf("    capacity = %ld\n", stk->capacity);
    printf("    data[%p]\n", stk->data);
    printf("{\n");
    for (ssize_t i = 0; i < stk->capacity; i++)
    {
        printf("    [%zd] = %d\n", i, stk->data[i]);
    }
    printf("    }\n");
    printf("}\n");
}
