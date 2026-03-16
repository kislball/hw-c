#include "data.h"
#include <stdlib.h>

Input* inputNew(int cities, int capitals, int roads)
{
    (void)roads;

    Input* res = calloc(1, sizeof(*res));
    if (res == nullptr)
        return nullptr;

    res->totalCapitals = capitals;
    res->totalCities = cities;

    res->matrix = calloc(res->totalCities * res->totalCities, sizeof(*res->matrix));
    if (res->matrix == nullptr) {
        free(res);
        return nullptr;
    }

    res->isCapital = calloc(res->totalCities, sizeof(*res->isCapital));
    if (res->isCapital == nullptr) {
        free(res->matrix);
        free(res);
        return nullptr;
    }

    return res;
}

void inputFree(Input** i)
{
    Input* input = *i;
    free(input->matrix);
    free(input->isCapital);
    free(input);

    *i = nullptr;
}

Road inputGetRoad(Input* input, unsigned i, unsigned j)
{
    Road r = { i, j, input->matrix[i * input->totalCities + j] };
    return r;
}

void inputSetRoad(Input* input, unsigned i, unsigned j, unsigned len)
{
    input->matrix[i * input->totalCities + j] = len;
    input->matrix[j * input->totalCities + i] = len;
}

Input* inputRead(FILE* f)
{
    int cities = 0, roads = 0;
    fscanf(f, "%d %d\n", &cities, &roads);

    Input* input = inputNew(cities, cities, roads);

    for (int k = 0; k < roads; k++) {
        int a = 0, b = 0, l = 0;
        fscanf(f, "%d %d %d\n", &a, &b, &l);
        inputSetRoad(input, a, b, l);
    }

    int capitals = 0;
    fscanf(f, "%d\n", &capitals);

    input->totalCapitals = capitals;

    for (int i = 0; i < capitals; i++) {
        int capital = 0;
        fscanf(f, "%d\n", &capital);
        input->isCapital[capital] = true;
    }

    return input;
}
