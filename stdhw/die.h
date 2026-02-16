#pragma once

#define dieIf(condition, text)                                                                      \
    do {                                                                                            \
        if (condition) {                                                                            \
            fprintf(stderr, "died because %s, %s:%d:\t%s\n", text, __FILE__, __LINE__, #condition); \
            exit(EXIT_FAILURE);                                                                     \
        }                                                                                           \
    } while (0)
