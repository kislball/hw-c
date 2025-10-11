#pragma once
#include <stdbool.h>

// Элемент на стеке.
typedef struct StackNode {
    int value;
    struct StackNode* next;
} StackNode;

// Стек, поддерживающий операции push, pop, peek.
typedef struct {
    StackNode* head;
    int size;
} Stack;

// Инициализирует новый экземпляр структуры стек.
Stack stackNew();
// Освобождает память, занимаемую стеком.
void stackDelete(Stack* stack);
// Добавляет элемент на вершину стека. Возвращает false в случае ошибки, true - в ином случае.
bool stackPush(Stack* stack, int vlaue);
// Возвращает элемент с вершины стека, а затем убирает его. По указателю во втором аргументе устанавливается значение
// true если в стеке есть элемент на вершине, в ином случае false.
int stackPop(Stack* stack, bool* isSuccessful);
// Возвращает элемент с вершины стека. По указателю во втором аргументе устанавливается значение
// true если в стеке есть элемент на вершине, в ином случае false.
int stackPeek(Stack* stack, bool* isSuccessful);
