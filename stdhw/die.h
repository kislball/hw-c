#pragma once

#define dieIf(condition, text)                                                                      \
    do {                                                                                            \
        if (condition) {                                                                            \
            fprintf(stderr, "died because %s, %s:%d:\t%s\n", text, __FILE__, __LINE__, #condition); \
            exit(EXIT_FAILURE);                                                                     \
        }                                                                                           \
    } while (0)

#define dieIfNot(condition, text) dieIf(!(condition), text)
