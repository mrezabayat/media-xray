#pragma once
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_TRUE(cond)                       \
    do                                          \
    {                                           \
        if (!(cond))                            \
        {                                       \
            fprintf(stderr,                     \
                    "[FAIL] %s:%d: %s\n",       \
                    __FILE__, __LINE__, #cond); \
            exit(EXIT_FAILURE);                 \
        }                                       \
    } while (0)

#define ASSERT_EQ(a, b)                          \
    do                                           \
    {                                            \
        if ((a) != (b))                          \
        {                                        \
            fprintf(stderr,                      \
                    "[FAIL] %s:%d: %s != %s\n",  \
                    __FILE__, __LINE__, #a, #b); \
            exit(EXIT_FAILURE);                  \
        }                                        \
    } while (0)
