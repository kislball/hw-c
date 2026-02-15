#pragma once

#include "destruct.h"
#include <stdbool.h>

// Очередь
// Считается, что с момента добавления элемента в очередь, память принадлежит
// очереди и очищается деструктором, предоставленным очереди.
typedef struct Queue Queue;

// Выделяет память под очередь
Queue* queueNew(void);
// Выделяет память под очередь с заданным деструктором
Queue* queueNewWithDestructor(Destructor);
// Освобождает очередь
void queueFree(Queue**);
// Добавляет элемент в очередь
void queueEnqueue(Queue*, void*);
// Вытаскивает элемент из очереди. Возвращает true если очередь не пуста(и записывает значение по указателю на int),
// в ином случае false.
// Последнее значение определяет, запускать ли деструктор для значения
bool queueDequeue(Queue*, void**, bool destruct);
