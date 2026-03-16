#pragma once
#include "graph.h"

typedef struct PQueue PQueue;

PQueue* pqueueNew();
void pqueueEnqueue(PQueue*, Road road);
Road pqueueDequeue(PQueue*, bool* has);
bool pqueueIsEmpty(PQueue*);
void pqueueFree(PQueue**);
