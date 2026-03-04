#include "map.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* fileName = nullptr;
static Map* data = nullptr;

void writeDb()
{
    FILE* f = fopen(fileName, "w");
    if (!f) {
        fprintf(stderr, "Failed to write DB: %s\n", strerror(errno));
        exit(1);
    }
    mapExport(data, f);
    fclose(f);
}

bool runCommand(char* cmd)
{
    char commandName[16] = { };
    char argument[512] = { };
    sscanf(cmd, "%15[^ \n] %511[^\n]", commandName, argument);

    if (!strcmp(commandName, "quit"))
        return false;
    else if (!strcmp(commandName, "save")) {
        writeDb();
        return true;
    } else if (!strcmp(commandName, "delete")) {
        mapDelete(&data, argument);
    } else if (!strcmp(commandName, "find")) {
        char* value = nullptr;
        bool ok = mapGet(data, argument, &value);
        if (ok) {
            printf("%s -> %s\n", argument, value);
            free(value);
        } else {
            fprintf(stderr, "Airport \"%s\" not found\n", argument);
        }
        return true;
    } else if (!strcmp(commandName, "add")) {
        char code[16] = { };
        char name[128] = { };
        sscanf(argument, "%15[^:]:%127[^\n]", code, name);
        mapInsert(&data, code, name);
        printf("Added record %s -> %s\n", code, name);
        return true;
    } else {
        fprintf(stderr, "Unknown command\n");
        return true;
    }

    return true; // to avoid compiler warnings
}

void readDb()
{
    FILE* f = fopen(fileName, "r");
    if (!f) {
        fprintf(stderr, "Failed to open DB: %s\n", strerror(errno));
        exit(1);
    }

    if (data)
        mapFree(&data);
    data = mapImport(f);
    fclose(f);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Correct usage: %s <filename>", argv[0]);
        return 1;
    }

    fileName = argv[1];
    readDb();

    char buffer[512] = { };

    while (true) {
        printf(">: ");
        fgets(buffer, 512, stdin);
        if (!runCommand(buffer))
            break;
    }

    mapFree(&data);
    return 0;
}
