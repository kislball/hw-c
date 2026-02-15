#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_BUILDER_NOT_NULL(builder) assert((builder != NULL) && "Builder must not be NULL")

typedef struct StringBuilder {
    char* buffer;
    size_t capacity;
    size_t size;
} StringBuilder;

StringBuilder* stringBuilderNew(void)
{
    StringBuilder* builder = calloc(1, sizeof(*builder));
    assert(builder != NULL && "Failed to allocate string builder");

    builder->size = 0;
    builder->capacity = 16;
    builder->buffer = calloc(builder->capacity, sizeof(char));
    if (builder->buffer == NULL) {
        free(builder);
        assert(false && "Failed to allocate string buffer");
    }

    return builder;
}

void stringBuilderFree(StringBuilder** builder)
{
    ASSERT_BUILDER_NOT_NULL(builder);
    ASSERT_BUILDER_NOT_NULL(*builder);
    free((**builder).buffer);
    free(*builder);
    *builder = NULL;
}

char* stringBuild(StringBuilder* builder)
{
    ASSERT_BUILDER_NOT_NULL(builder);
    return strdup(builder->buffer);
}

static void stringBuilderExtend(StringBuilder* bldr)
{
    ASSERT_BUILDER_NOT_NULL(bldr);
    bldr->capacity *= 2;
    void* newAddr = realloc(bldr->buffer, bldr->capacity);
    assert(newAddr != NULL && "Failed to allocate more memory for string builder");
    bldr->buffer = newAddr;
}

void stringBuilderAppend(StringBuilder* bldr, char* string)
{
    ASSERT_BUILDER_NOT_NULL(bldr);
    size_t len = strlen(string);
    while (bldr->size + len + 1 > bldr->capacity)
        stringBuilderExtend(bldr);
    memcpy(bldr->buffer + bldr->size, string, len);
    bldr->buffer[bldr->size + len] = '\0';
    bldr->size += len;
}
