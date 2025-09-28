#include <stdio.h>
#include "stack.h"

int main()
{
    struct stack_t stk1 = {};
    
    printf("Enter the desired number of items in the stack: ");
    
    while (scanf("%zd", &stk1.capacity) != 1 || stk1.capacity < 0)
    {
        printf("You must enter the natural number: ");
        int ch = 0;
        while((ch = getchar()) != '\n') 
            continue;
    }

    StackInit(&stk1, stk1.capacity);

    printf("Enter the numbers you want to add to the stack(a non-numeric character for completion): ");
    USED_TYPE value = 0;

    while(scanf("%d", &value) == 1)
    {
        StackPush(&stk1, value);
    }
    
    int ch = 0;
    while((ch = getchar()) != '\n') 
        continue;

    StackErr_t err = NO_ERROR;
    for (ssize_t i = stk1.size; i > 0; i--)
    {
        USED_TYPE deliver_value = StackPop(&stk1, &err);
        if (err) 
        {
            StackDump(&stk1,__FILE__, __LINE__); // можешь впихнуть в stackverify
            printf("ошибка: %d", err);
        }
        printf("%d ", deliver_value);
    }
    printf("\ncapacity = %zd", stk1.capacity);

    StackDestroy(&stk1);

    return 0;
}
