#pragma once

#include <stdbool.h>

// Очередь
typedef struct Queue Queue;

// Выделяет память под очередь
Queue* queueNew(void);
// Освобождает очередь
void queueFree(Queue**);
// Добавляет элемент в очередь
void queueEnqueue(Queue*, void*);
// Вытаскивает элемент из очереди. Возвращает true если очередь не пуста(и записывает значение по указателю на int),
// в ином случае false.
bool queueDequeue(Queue*, void**);
