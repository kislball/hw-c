#include "queue.h"
#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_QUEUE_NOT_NULL(q) assert((q) != NULL && "Queue must be initialized")

typedef struct Queue {
    LinkedList* head;
    LinkedList* tail;
} Queue;

Queue* queueNew(void)
{
    Queue* q = calloc(1, sizeof(*q));
    q->head = linkedListNew();
    q->tail = linkedListNew();
    return q;
}

void queueAssertInvariant(Queue* q)
{
    if (linkedListCount(q->head) == 0)
        assert(linkedListCount(q->tail) == 0 && "Head is only empty if the tail is empty");
}

void queueSwapHeadAndTail(Queue* q)
{
    LinkedList* reversed = linkedListReverse(q->tail);
    linkedListFree(&q->tail);
    q->tail = linkedListNew();
    linkedListFree(&q->head);
    q->head = reversed;
}

void queueEnqueue(Queue* q, void* value)
{
    queueAssertInvariant(q);
    linkedListInsert(q->tail, linkedListCount(q->tail), value);
    if (linkedListCount(q->head) == 0)
        queueSwapHeadAndTail(q);
    queueAssertInvariant(q);
}

bool queueDequeue(Queue* q, void** value)
{
    int count = linkedListCount(q->head);

    queueAssertInvariant(q);
    bool has = linkedListGet(q->head, count - 1, value);
    if (!has)
        return false;
    assert(linkedListRemove(q->head, count - 1));
    if (linkedListCount(q->head) == 0)
        queueSwapHeadAndTail(q);
    queueAssertInvariant(q);

    return true;
}

void queueFree(Queue** q)
{
    ASSERT_QUEUE_NOT_NULL(*q);
    linkedListFree(&(*q)->head);
    linkedListFree(&(*q)->tail);
    free(*q);
    *q = NULL;
}
