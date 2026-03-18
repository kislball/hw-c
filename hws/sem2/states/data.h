#pragma once
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>

// Входные данные для алгоритма
typedef struct {
    unsigned totalCities;
    bool* isCapital;
    unsigned totalCapitals;

    // Таблица смежности
    unsigned* matrix;
} Input;

// Выделение памяти под ввод
Input* inputNew(int cities, int capitals, int roads);
// Чтение данных из файла
Input* inputRead(FILE* f);
// Получение длины дороги
Road inputGetRoad(Input*, unsigned i, unsigned j);
// Установка длины дороги
void inputSetRoad(Input*, unsigned i, unsigned j, unsigned len);
// Освобождение памяти
void inputFree(Input**);
