#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

Stack stackNew(void)
{
    Stack st = { .head = NULL, .size = 0 };
    return st;
}

bool stackPush(Stack* stack, int value)
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

int stackPeek(Stack* stack, bool* isSuccessful)
{
    if (stack->head == NULL) {
        *isSuccessful = false;
        return 0;
    } else {
        *isSuccessful = true;
        return stack->head->value;
    }
}

int stackPop(Stack* stack, bool* isSuccessful)
{
    int val = stackPeek(stack, isSuccessful);
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

