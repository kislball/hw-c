#pragma once

typedef struct StringBuilder StringBuilder;

StringBuilder* stringBuilderNew(void);
char* stringBuild(StringBuilder*);
void stringBuilderAppend(StringBuilder*, char*);
void stringBuilderFree(StringBuilder**);
