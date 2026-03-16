#pragma once

#include "data.h"
typedef struct {
    unsigned totalCities;
    unsigned* cities;
} State;

typedef struct {
    unsigned totalStates;
    State* states;
} Output;

State* stateNew();
void stateFree(State**);
void stateAdd(State*, unsigned);

Output* outputNew();
void outputAdd(Output*, State);
void outputFree(Output**);

Output* solve(Input*);
