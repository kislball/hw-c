#pragma once

#include <stdbool.h>

// Очередь
typedef struct Queue Queue;

// Выделяет память под очередь
Queue* queueNew(void);
// Освобождает очередь
void queueFree(Queue**);
// Добавляет элемент в очередь
void queueEnqueue(Queue*, int);
// Вытаскивает элемент из очереди
bool queueDequeue(Queue*, int*);
