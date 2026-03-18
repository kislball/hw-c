#pragma once
#include "data.h"

// Государство
typedef struct {
    unsigned totalCities;
    unsigned* cities;
} State;

// Результат работы алгоритма
typedef struct {
    unsigned totalStates;
    State* states;
} Output;

// Выделение памяти под новое государство
State* stateNew();
// Освобождение памяти
void stateFree(State**);
// Добавление нового города к государству
void stateAdd(State*, unsigned);

// Выделение памяти под результат работыё
Output* outputNew();
// Добавление нового государства к городу
void outputAdd(Output*, State);
// Освобождение памяти
void outputFree(Output**);

// Запуск алгоритма
Output* solve(Input*);
