#include "queue.h"
#include "destruct.h"
#include "die.h"
#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_QUEUE_NOT_NULL(q) dieIfNot((q) != NULL, "Queue must be initialized")

typedef struct Queue {
    LinkedList* head;
    LinkedList* tail;
    Destructor destruct;
} Queue;

Queue* queueNewWithDestructor(Destructor destruct)
{
    Queue* q = calloc(1, sizeof(*q));
    q->head = linkedListNewWithDestructor(destruct);
    q->tail = linkedListNewWithDestructor(destruct);
    q->destruct = destruct;
    return q;
}

Queue* queueNew(void)
{
    return queueNewWithDestructor(NULL);
}

void queueAssertInvariant(Queue* q)
{
    if (linkedListCount(q->head) == 0)
        dieIfNot(linkedListCount(q->tail) == 0, "Head is only empty if the tail is empty");
}

void queueSwapHeadAndTail(Queue* q)
{
    LinkedList* reversed = linkedListReverse(q->tail);
    linkedListFree(&q->tail);
    q->tail = linkedListNewWithDestructor(q->destruct);
    linkedListFree(&q->head);
    q->head = reversed;
}

void queueEnqueue(Queue* q, void* value)
{
    queueAssertInvariant(q);
    linkedListInsert(q->tail, linkedListCount(q->tail), value, false);
    if (linkedListCount(q->head) == 0)
        queueSwapHeadAndTail(q);
    queueAssertInvariant(q);
}

bool queueDequeue(Queue* q, void** value, bool destruct)
{
    int count = linkedListCount(q->head);

    queueAssertInvariant(q);
    bool has = linkedListGet(q->head, count - 1, value);
    if (!has)
        return false;
    bool ok = linkedListRemove(q->head, count - 1, destruct);
    dieIfNot(ok, "unreachable, bug");
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
