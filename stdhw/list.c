#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_LIST_NOT_NULL(list) assert((list) != NULL && "List must have been initialized")
#define ASSERT_ITERATOR_NOT_NULL(iterator) assert(( iterator ) != NULL && "Iterator must have been initialized")
// now internal
#define LINKED_LIST_FOREACH(list, node) for (LinkedListNode* ( node ) = (list)->head; (node) != NULL; (node) = (node)->next)

// Элемент связного списка
typedef struct LinkedListNode {
    int value;
    struct LinkedListNode* next;
} LinkedListNode;

// Связный список
typedef struct LinkedList {
    LinkedListNode* head;
    int size;
} LinkedList;

typedef struct LinkedListIterator {
    LinkedListNode* current;
} LinkedListIterator;

LinkedListIterator* linkedListIteratorNew(LinkedList* list)
{
    ASSERT_LIST_NOT_NULL(list);
    LinkedListIterator* iterator = calloc(1, sizeof(*iterator));
    iterator->current = list->head;
    return iterator;
}

bool linkedListIteratorNext(LinkedListIterator* iterator, int* value)
{
    ASSERT_ITERATOR_NOT_NULL(iterator);
    if (iterator->current == NULL)
        return false;
    *value = iterator->current->value;
    iterator->current = iterator->current->next;
    return true;
}

void linkedListIteratorFree(LinkedListIterator** iterator)
{
    ASSERT_ITERATOR_NOT_NULL(*iterator);
    free(*iterator);
    *iterator = NULL;
}

LinkedList* linkedListNew()
{
    LinkedList* list = calloc(1, sizeof(*list));
    list->head = NULL;
    return list;
}

void linkedListFree(LinkedList** list)
{
    ASSERT_LIST_NOT_NULL(*list);
    free(*list);
    *list = NULL;
}

bool linkedListInsertNode(LinkedList* list, int index, LinkedListNode* node)
{
    ASSERT_LIST_NOT_NULL(list);
    if (index < 0)
        return false;
    if (index == 0) {
        node->next = list->head;
        list->head = node;
        list->size++;
        return true;
    }

    LinkedListNode* ptr = linkedListGetPointer(list, index - 1);
    if (ptr == NULL)
        return false;

    node->next = ptr->next;
    ptr->next = node;
    list->size++;
    return true;
}

bool linkedListInsert(LinkedList* list, int index, int value)
{
    ASSERT_LIST_NOT_NULL(list);
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
    ASSERT_LIST_NOT_NULL(list);
    if (index < 0)
        return NULL;
    LinkedListNode* ptr = list->head;
    for (int i = 0; i < index && ptr != NULL; i++) {
        ptr = ptr->next;
    }
    return ptr;
}

bool linkedListGet(LinkedList* list, int index, int* value)
{
    ASSERT_LIST_NOT_NULL(list);
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
    ASSERT_LIST_NOT_NULL(list);
    if (index < 0)
        return false;
    if (index == 0) {
        if (list->head == NULL)
            return false;
        LinkedListNode* next = list->head->next;
        free(list->head);
        list->head = next;
        list->size--;
        return true;
    }

    LinkedListNode* before = linkedListGetPointer(list, index - 1);
    if (before == NULL)
        return false;
    LinkedListNode* toBeRemoved = before->next;
    if (toBeRemoved == NULL)
        return false;
    before->next = toBeRemoved->next;
    list->size--;
    free(toBeRemoved);
    return true;
}

void linkedListAppend(LinkedList* to, LinkedList* from)
{
    ASSERT_LIST_NOT_NULL(to);
    ASSERT_LIST_NOT_NULL(from);
    to->size += from->size;
    if (to->head == NULL) {
        to->head = from->head;
        from->head = NULL;
        return;
    }
    LinkedListNode* last = to->head;
    while (last->next != NULL)
        last = last->next;
    last->next = from->head;
    from->head = NULL;
}

int linkedListCount(LinkedList* list)
{
    return list->size;
}

void linkedListDelete(LinkedList* list)
{
    ASSERT_LIST_NOT_NULL(list);
    while (linkedListRemove(list, 0)) { }
}

void intPrinter(int value)
{
    printf("%d ", value);
}

void linkedListPrint(LinkedList* list, void (*printer)(int))
{
    ASSERT_LIST_NOT_NULL(list);
    LINKED_LIST_FOREACH(list, node)
    {
        printer(node->value);
    }
}

void linkedListPrintStdout(LinkedList* list)
{
    ASSERT_LIST_NOT_NULL(list);
    linkedListPrint(list, intPrinter);
}
