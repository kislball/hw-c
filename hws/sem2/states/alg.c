#include "alg.h"
#include "data.h"
#include "queue.h"
#include <assert.h>
#include <stdlib.h>

State* stateNew()
{
    State* res = calloc(1, sizeof(*res));
    if (res == nullptr)
        return nullptr;

    res->totalCities = 0;
    res->cities = nullptr;

    return res;
}

void stateFree(State** s)
{
    State* state = *s;
    free(state->cities);
    free(state);

    *s = nullptr;
}

void stateAdd(State* state, unsigned city)
{
    unsigned* newCities = realloc(state->cities, (state->totalCities + 1) * sizeof(unsigned));
    if (newCities == nullptr)
        return;

    state->cities = newCities;
    state->cities[state->totalCities] = city;
    state->totalCities++;
}

Output* outputNew()
{
    Output* res = calloc(1, sizeof(*res));
    if (res == nullptr)
        return nullptr;

    res->totalStates = 0;
    res->states = nullptr;

    return res;
}

void outputAdd(Output* output, State state)
{
    State* newStates = realloc(output->states, (output->totalStates + 1) * sizeof(State));
    if (newStates == nullptr)
        return;

    output->states = newStates;
    output->states[output->totalStates] = state;
    output->totalStates++;
}

void outputFree(Output** o)
{
    Output* output = *o;
    free(output->states);
    free(output);

    *o = nullptr;
}

Output* solve(Input* inp)
{
    Output* out = outputNew();
    PQueue** stateQueues = calloc(inp->totalCapitals, sizeof(*stateQueues));
    State** states = calloc(inp->totalCapitals, sizeof(*states));
    unsigned* stateCapitals = calloc(inp->totalCapitals, sizeof(*stateCapitals));
    bool* cityAdded = calloc(inp->totalCities, sizeof(*cityAdded));

    unsigned addedStates = 0;

    for (unsigned i = 0; i < inp->totalCities; i++) {
        if (inp->isCapital[i]) {
            stateQueues[addedStates] = pqueueNew();
            stateCapitals[addedStates] = i;
            states[addedStates] = stateNew();
            cityAdded[i] = true;
            stateAdd(states[addedStates], i);

            for (unsigned j = 0; j < inp->totalCities; j++) {
                unsigned len = inp->matrix[i * inp->totalCities + j];
                Road r = { .from = i, .to = j, .length = len };
                if (len && i != j)
                    pqueueEnqueue(stateQueues[addedStates], r);
            }

            addedStates++;
        }
    }
    assert(addedStates == inp->totalCapitals);

    unsigned skippedInARow = 0;
    for (unsigned ord = 0; skippedInARow != inp->totalCapitals; ord++) {
        unsigned stateId = ord % inp->totalCapitals;
        PQueue* q = stateQueues[ord % inp->totalCapitals];
        if (pqueueIsEmpty(q)) {
            skippedInARow++;
            continue;
        } else {
            skippedInARow = 0;
        }

        bool ok = false;
        Road shortestRoad = pqueueDequeue(q, &ok);
        assert(ok);

        if (cityAdded[shortestRoad.to]) {
            skippedInARow++;
            continue;
        }
        stateAdd(states[stateId], shortestRoad.to);

        unsigned i = shortestRoad.to;
        cityAdded[i] = true;

        for (unsigned j = 0; j < inp->totalCities; j++) {
            unsigned len = inp->matrix[i * inp->totalCities + j];
            Road r = { .from = i, .to = j, .length = len };
            if (len && i != j)
                pqueueEnqueue(stateQueues[stateId], r);
        }
    }

    for (unsigned i = 0; i < addedStates; i++) {
        outputAdd(out, *states[i]);
        // stateFree(&states[i]);
    }

    free(states);
    free(stateQueues);
    free(cityAdded);
    free(stateCapitals);
    return out;
}
