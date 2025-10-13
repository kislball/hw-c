#pragma once
#include <stdbool.h>

typedef struct LinkedListNode {
    int value;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
} LinkedList;

bool linkedListInsert(LinkedList* list, int index, int value);
bool linkedListGet(LinkedList* list, int index, int* value);
LinkedListNode* linkedListGetPointer(LinkedList* list, int index);
bool linkedListRemove(LinkedList* list, int index);
void linkedListAppend(LinkedList* to, LinkedList* from);
int linkedListCount(LinkedList* list);

LinkedList linkedListNew();
void linkedListDelete(LinkedList* list);
void linkedListPrint(LinkedList* list, void (*print)(int));
void linkedListPrintStdout(LinkedList* list);

#define LINKED_LIST_FOREACH(list, node) for (LinkedListNode* node = (list)->head; (node) != NULL; (node) = (node)->next)
