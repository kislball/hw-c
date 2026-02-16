#include "common.h"
#include "display.h"
#include "csv.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char* name)
{
	printf("%s usage: %s <filename>\n", name, name);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "%s: expected 2 arguments, got - %d\n", argv[0], argc);
		usage(argv[0]);
		return 1;
	}
	FILE* fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		fprintf(stderr, "%s: failed to open %s: %s\n", argv[0], argv[1], strerror(errno));
		return 1;
	}
	CSVTable* table = csvNew();
	csvFeedFile(table, fptr);
	fclose(fptr);
	char* result = dataCellRenderTable(
		csvGetCellsView(table),
		csvWidth(table),
		csvHeight(table)
	);
	printf("%s", result);

	free(result);
	csvFree(&table);
	return 0;
}
