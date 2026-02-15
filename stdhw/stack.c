#include "stack.h"
#include "destruct.h"
#include <stdbool.h>
#include <stdlib.h>

Stack stackNewWithDestructor(Destructor destruct)
{
    Stack st = { .head = NULL, .size = 0, .destruct = destruct };
    return st;
}

Stack stackNew(void)
{
    return stackNewWithDestructor(NULL);
}

bool stackPush(Stack* stack, void* value)
{
    StackNode* node = malloc(sizeof(StackNode));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = stack->head;
    stack->size++;

    stack->head = node;
    return true;
}

void* stackPeek(Stack* stack, bool* isSuccessful)
{
    if (stack->head == NULL) {
        *isSuccessful = false;
        return 0;
    } else {
        *isSuccessful = true;
        return stack->head->value;
    }
}

void* stackPop(Stack* stack, bool* isSuccessful)
{
    void* val = stackPeek(stack, isSuccessful);
    if (!*isSuccessful) {
        return 0;
    }

    StackNode* head = stack->head;
    stack->head = head->next;
    stack->size--;

    free(head);

    return val;
}

void stackDelete(Stack* stack)
{
    bool has = true;
    while (has) {
        stackPop(stack, &has);
    }
    stack->head = NULL;
    stack->size = 0;
}
