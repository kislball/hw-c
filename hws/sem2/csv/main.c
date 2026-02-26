#include "common.h"
#include "csv.h"
#include "display.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    char* inputName = "input.csv";
    char* outputName = "output.txt";
    if (argc >= 2)
        inputName = argv[1];
    if (argc >= 3)
        outputName = argv[2];
    assert(inputName != nullptr && outputName != nullptr);

    FILE* fptr = fopen(inputName, "r");
    if (fptr == nullptr) {
        fprintf(stderr, "%s: failed to open %s: %s\n", argv[0], inputName, strerror(errno));
        return 1;
    }
    CSVTable* table = csvNew();
    csvFeedFile(table, fptr);
    fclose(fptr);
    char* result = dataCellRenderTable(
        csvGetCellsView(table),
        csvWidth(table),
        csvHeight(table));

    FILE* out = fopen(outputName, "w");
    if (out == nullptr) {
        fprintf(stderr, "%s: failed to open %s: %s\n", argv[0], outputName, strerror(errno));
        free(result);
        csvFree(&table);
        return 1;
    }
    fprintf(out, "%s", result);
    fclose(out);

    free(result);
    csvFree(&table);
    return 0;
}
