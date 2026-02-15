#include "strutil.h"
#include "strbuild.h"
#include "string.h"
#include <assert.h>
#include <stdlib.h>

char* padRight(char* source, size_t targetSize, char character)
{
    StringBuilder* builder = stringBuilderNew();
    stringBuilderAppend(builder, source);
    int diff = -(int)strlen(source) + (int)targetSize;
    if (diff <= 0)
        return strdup(source); // Чтобы гарантировать то, что возвращаемая память уникальна

    char* temporary = calloc(diff + 1, sizeof(char));
    assert(temporary != NULL && "Failed to allocate temporary bytes");

    memset(temporary, character, diff);
    temporary[diff] = '\0';
    stringBuilderAppend(builder, temporary);
    free(temporary);

    char* result = stringBuild(builder);
    stringBuilderFree(&builder);
    return result;
}

char* padLeft(char* source, size_t targetSize, char character)
{
    StringBuilder* builder = stringBuilderNew();
    int diff = -(int)strlen(source) + (int)targetSize;
    if (diff <= 0)
        return strdup(source); // Чтобы гарантировать то, что возвращаемая память уникальна

    char* temporary = calloc(diff + 1, sizeof(char));
    assert(temporary != NULL && "Failed to allocate temporary bytes");

    memset(temporary, character, diff);
    temporary[diff] = '\0';
    stringBuilderAppend(builder, temporary);
    free(temporary);
    stringBuilderAppend(builder, source);

    char* result = stringBuild(builder);
    stringBuilderFree(&builder);
    return result;
}
