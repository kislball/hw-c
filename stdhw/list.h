#pragma once
#include <stdbool.h>

typedef struct LinkedList LinkedList;
typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedListIterator LinkedListIterator;

LinkedListIterator* linkedListIteratorNew(LinkedList* list);
bool linkedListIteratorNext(LinkedListIterator* iterator, int* value);
void linkedListIteratorFree(LinkedListIterator** iterator);

// Добавление элемента в список по заданному индексу
bool linkedListInsert(LinkedList* list, int index, int value);
// Получение элемента по заданному списку
bool linkedListGet(LinkedList* list, int index, int* value);
// Получение указателя на узел по заданному индексу
LinkedListNode* linkedListGetPointer(LinkedList* list, int index);
// Удаление элемента из списка по задданому индексу
bool linkedListRemove(LinkedList* list, int index);
// Добавление элементов из from в to
void linkedListAppend(LinkedList* to, LinkedList* from);
// Возвращает количество элементов в списке
int linkedListCount(LinkedList* list);

// Создание нового связного списка
LinkedList* linkedListNew();
// Удаление всех элементов связного списка
void linkedListDelete(LinkedList* list);
// Освобождение списка
void linkedListFree(LinkedList** list);
// Вывод всех элементов списка используя функцию print(предоставляется пользователем)
void linkedListPrint(LinkedList* list, void (*print)(int));
// Вывод всех элементов списка в стандартный вывод
void linkedListPrintStdout(LinkedList* list);
