#include "stack.h"
#include "destruct.h"
#include <stdbool.h>
#include <stdlib.h>

Stack stackNewWithDestructor(Destructor destruct)
{
    Stack st = { .head = nullptr, .size = 0, .destruct = destruct };
    return st;
}

Stack stackNew(void)
{
    return stackNewWithDestructor(nullptr);
}

bool stackPush(Stack* stack, void* value)
{
    StackNode* node = malloc(sizeof(StackNode));
    if (node == nullptr) {
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
    if (stack->head == nullptr) {
        *isSuccessful = false;
        return nullptr;
    } else {
        *isSuccessful = true;
        return stack->head->value;
    }
}

void* stackPop(Stack* stack, bool* isSuccessful)
{
    void* val = stackPeek(stack, isSuccessful);
    if (!*isSuccessful) {
        return nullptr;
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
    stack->head = nullptr;
    stack->size = 0;
}
