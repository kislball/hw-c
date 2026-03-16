#pragma once
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    unsigned totalCities;
    bool* isCapital;
    unsigned totalCapitals;

    unsigned* matrix;
} Input;

Input* inputNew(int cities, int capitals, int roads);
Input* inputRead(FILE* f);
Road inputGetRoad(Input*, unsigned i, unsigned j);
void inputSetRoad(Input*, unsigned i, unsigned j, unsigned len);
void inputFree(Input**);
