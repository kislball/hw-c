#include "common.h"
#include "csv.h"
#include "display.h"
#include <stdlib.h>
#include <string.h>

char* prettyCsv(char* data)
{
    CSVTable* table = csvNew();
    data = strdup(data);
    char* result = nullptr;

    for (char* segment = strtok(data, "\n"); segment; segment = strtok(nullptr, "\n")) {
        bool ok = csvFeedLine(table, segment);
        if (!ok)
            goto final;
    }
    result = dataCellRenderTable(csvGetCellsView(table), csvWidth(table), csvHeight(table));

final:
    free(data);
    csvFree(&table);
    return result;
}
