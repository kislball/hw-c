#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

Stack stackNew()
{
    Stack st = { .head = NULL };
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

    stack->head = node;
    return true;
}

int stackPeek(Stack* stack, bool* has)
{
    if (stack->head == NULL) {
        *has = false;
        return 0;
    } else {
        *has = true;
        return stack->head->value;
    }
}

int stackPop(Stack* stack, bool* has)
{
    int val = stackPeek(stack, has);
    if (!*has) {
        return 0;
    }

    StackNode* head = stack->head;
    stack->head = head->next;
    free(head);

    return val;
}

void stackDelete(Stack* stack)
{
    bool has = true;
    while (has) {
        stackPop(stack, &has);
    }
}
