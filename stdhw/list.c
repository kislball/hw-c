#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

LinkedList linkedListNew()
{
    LinkedList list = { .head = NULL };
    return list;
}

bool linkedListInsertNode(LinkedList* list, int index, LinkedListNode* node)
{
    if (index < 0)
        return false;
    if (index == 0) {
        node->next = list->head;
        list->head = node;
        return true;
    }

    LinkedListNode* ptr = linkedListGetPointer(list, index - 1);
    if (ptr == NULL)
        return false;

    node->next = ptr->next;
    ptr->next = node;
    return true;
}

bool linkedListInsert(LinkedList* list, int index, int value)
{
    if (index < 0)
        return false;
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->value = value;
    bool ok = linkedListInsertNode(list, index, node);
    if (!ok)
        free(node);
    return ok;
}

LinkedListNode* linkedListGetPointer(LinkedList* list, int index)
{
    if (index < 0)
        return false;
    LinkedListNode* ptr = list->head;
    for (int i = 0; i < index && ptr != NULL; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

bool linkedListGet(LinkedList* list, int index, int* value)
{
    if (index < 0)
        return false;
    LinkedListNode* ptr = linkedListGetPointer(list, index);
    if (ptr == NULL)
        return false;
    else {
        if (value != NULL)
            *value = ptr->value;
        return true;
    }
}

bool linkedListRemove(LinkedList* list, int index)
{
    if (index < 0)
        return false;
    if (index == 0) {
        if (list->head == NULL)
            return false;
        LinkedListNode* next = list->head->next;
        free(list->head);
        list->head = next;
        return true;
    }

    LinkedListNode* before = linkedListGetPointer(list, index - 1);
    if (before == NULL)
        assert(false && "UNREACHABLE");
    LinkedListNode* toBeRemoved = before->next;
    if (toBeRemoved == NULL)
        return false;
    before->next = toBeRemoved->next;
    free(toBeRemoved);
    return true;
}

void linkedListAppend(LinkedList* list, LinkedList* from)
{
    LinkedListNode* last = list->head;
    while (last->next != NULL)
        last = last->next;
    last->next = from->head;
    from->head = NULL;
}

int linkedListCount(LinkedList* list)
{
    int i = 0;
    LINKED_LIST_FOREACH(list, node)
    {
        i++;
    }
    return i;
}

void linkedListDelete(LinkedList* list)
{
    while (linkedListRemove(list, 0)) { }
}

void intPrinter(int value)
{
    printf("%d ", value);
}

void linkedListPrint(LinkedList* list, void (*printer)(int))
{
    LINKED_LIST_FOREACH(list, node)
    {
        printer(node->value);
    }
}

void linkedListPrintStdout(LinkedList* list)
{
    linkedListPrint(list, intPrinter);
}
