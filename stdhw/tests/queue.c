#include <assert.h>
#include <stdhw.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Queue* q = queueNew();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    queueEnqueue(q, &a);
    queueEnqueue(q, &b);
    queueEnqueue(q, &c);

    void* value = 0;
    assert(queueDequeue(q, &value, false) && *(int*)value == 1 && "Queue outputs elements in correct order");
    assert(queueDequeue(q, &value, false) && *(int*)value == 2 && "Queue outputs elements in correct order");
    queueEnqueue(q, &d);
    assert(queueDequeue(q, &value, false) && *(int*)value == 3 && "Queue outputs elements in correct order");
    assert(queueDequeue(q, &value, false) && *(int*)value == 4 && "Queue outputs elements in correct order");
    assert(!queueDequeue(q, &value, false) && "Queue is empty");

    queueFree(&q);
    assert(q == NULL && "Pointer must have been deinitialized");
    return 0;
}
