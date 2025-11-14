#pragma once
#include <stdhw.h>

// Встраивает элемент в связаный список, сохраняя отсортированность в случае, если список уже отсортирован.
int sortedLinkedListInsert(LinkedList* list, int value);
