#include "queue.h"
#include <stdlib.h>

typedef struct PQueue {
    unsigned capacity;
    unsigned len;
    Road* heap;
} PQueue;

void pqueueAllocHeap(PQueue* q)
{
    Road* new = realloc(q->heap, q->capacity * sizeof(Road));
    if (new == nullptr)
        return;
    q->heap = new;
}

PQueue* pqueueNew()
{
    PQueue* q = calloc(1, sizeof(*q));

    q->capacity = 16;
    q->len = 0;
    pqueueAllocHeap(q);

    return q;
}

void pqueueEnsureFits(PQueue* q, unsigned newSize)
{
    while (q->capacity <= newSize) {
        q->capacity *= 2;
        pqueueAllocHeap(q);
    }
}

void pqueueFree(PQueue** q)
{
    PQueue* qu = *q;
    free(qu->heap);
    free(*q);
    *q = nullptr;
}

void pqueueSiftDown(PQueue* q, unsigned i)
{
    while (2 * i + 1 < q->len) {
        unsigned left = 2 * i + 1;
        unsigned right = 2 * i + 2;

        unsigned j = left;

        if (right < q->len && q->heap[right].length < q->heap[left].length) {
            j = right;
        }

        if (q->heap[i].length <= q->heap[j].length) {
            break;
        }

        Road temp = q->heap[i];
        q->heap[i] = q->heap[j];
        q->heap[j] = temp;

        i = j;
    }
}

void pqueueSiftUp(PQueue* q, unsigned i)
{
    while (i > 0 && q->heap[i].length < q->heap[(i - 1) / 2].length) {
        Road temp = q->heap[i];
        q->heap[i] = q->heap[(i - 1) / 2];
        q->heap[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void pqueueEnqueue(PQueue* q, Road road)
{
    q->len++;
    pqueueEnsureFits(q, q->len);

    q->heap[q->len - 1] = road;
    pqueueSiftUp(q, q->len - 1);
}

Road pqueueDequeue(PQueue* q, bool* has)
{
    if (q->len == 0) {
        *has = false;
        Road el = { .from = 0, .to = 0, .length = 0 };
        return el;
    }
    Road target = q->heap[0];
    *has = true;

    q->heap[0] = q->heap[--q->len];
    pqueueSiftDown(q, 0);

    return target;
}

bool pqueueIsEmpty(PQueue* q)
{
    return q->len == 0;
}
