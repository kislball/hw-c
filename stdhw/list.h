#pragma once
#include "destruct.h"
#include <stdbool.h>

// Связный список. Считаеся, что с момента добавления элемента в список,
// он принадлежит списку, т.е. очищается исключительно самим списком используя деструктор.
typedef struct LinkedList LinkedList;
// Узел в связном списке
typedef struct LinkedListNode LinkedListNode;
// Итератор для связного списка
typedef struct LinkedListIterator LinkedListIterator;

// Создание нового итератора
LinkedListIterator* linkedListIteratorNew(LinkedList* list);
// Получение следующего элемента в связном списке с помощью итератора.
// Сохраняет значение в указатель value, возвращает true если было получено
// новое значение, в ином случае false.
bool linkedListIteratorNext(LinkedListIterator* iterator, void** value);
// Освобождает итератор.
void linkedListIteratorFree(LinkedListIterator** iterator);

// Добавление элемента в список по заданному индексу
// При значении true в аргументе destroyIfFailed, функция запустит деструктор для элемента
// при ошибке встраивания.
bool linkedListInsert(LinkedList* list, int index, void* value, bool destroyIfFailed);
// Получение элемента по заданному списку
bool linkedListGet(LinkedList* list, int index, void** value);
// Получение указателя на узел по заданному индексу
LinkedListNode* linkedListGetPointer(LinkedList* list, int index);
// Удаление элемента из списка по задданому индексу
// При значении последнего аргумента true, функция запустит деструктор для
// удаляемого элемента(если деструктор был определён).
bool linkedListRemove(LinkedList* list, int index, bool destroy);
// Добавление элементов из from в to
// При этом элементы списка from будут перемещены, а он сам будет опустошён
void linkedListAppend(LinkedList* to, LinkedList* from);
// Возвращает количество элементов в списке
int linkedListCount(LinkedList* list);
// Возвращает новый обращённый связный список
LinkedList* linkedListReverse(LinkedList*);

// Создание нового связного списка
LinkedList* linkedListNew(void);
// Создание нового связного списка с указанным деструктором элементов
LinkedList* linkedListNewWithDestructor(Destructor);
// Удаление всех элементов связного списка
void linkedListDelete(LinkedList* list);
// Освобождение списка
void linkedListFree(LinkedList** list);
// Вывод всех элементов списка используя функцию print(предоставляется пользователем)
void linkedListPrint(LinkedList* list, void (*print)(void*));
// Вывод всех элементов списка в стандартный вывод
void linkedListPrintStdout(LinkedList* list);
