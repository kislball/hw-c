#pragma once
#include "graph.h"

// Очередь с приоритетами по типу Road
typedef struct PQueue PQueue;

// Выделение памяти под очерредь
PQueue* pqueueNew();
// Добавление элемента очереди с приоритетом road->len
void pqueueEnqueue(PQueue*, Road road);
// Получение элемента из очереди с наименьшим приоритетом.
// has устанавливается в true если элемент найден, false в ином случае
Road pqueueDequeue(PQueue*, bool* has);
// Пуста ли очередь
bool pqueueIsEmpty(PQueue*);
// Освобождение занимаемой памяти
void pqueueFree(PQueue**);
