#include "alg.h"
#include "data.h"
#include <errno.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 2)
        return 1;
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("%s: failed to open file: %s\n", argv[0], strerror(errno));
        return 1;
    }
    Input* input = inputRead(f);
    Output* solution = solve(input);

    for (unsigned i = 0; i < solution->totalStates; i++) {
        State state = solution->states[i];
        printf("%d: ", i);
        for (unsigned j = 0; j < state.totalCities; j++) {
            printf("%d ", state.cities[j]);
        }
        printf("\n");
    }

    inputFree(&input);
    outputFree(&solution);
    fclose(f);
    return 0;
}
