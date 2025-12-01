#include <assert.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Queue* q = queueNew();
    queueEnqueue(q, 1);
    queueEnqueue(q, 2);
    queueEnqueue(q, 3);

    int value = 0;
    assert(queueDequeue(q, &value) && value == 1 && "Queue outputs elements in correct order");
    assert(queueDequeue(q, &value) && value == 2 && "Queue outputs elements in correct order");
    queueEnqueue(q, 4);
    assert(queueDequeue(q, &value) && value == 3 && "Queue outputs elements in correct order");
    assert(queueDequeue(q, &value) && value == 4 && "Queue outputs elements in correct order");
    assert(!queueDequeue(q, &value) && "Queue is empty");

    queueFree(&q);
    assert(q == NULL && "Pointer must have been deinitialized");
    return 0;
}
