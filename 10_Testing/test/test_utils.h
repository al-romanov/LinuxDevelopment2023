#ifndef TESTING_TEST_UTILS_H
#define TESTING_TEST_UTILS_H

#include <stdio.h>

#define C_RED(s)     "\033[31;1m" s "\033[0m"
#define C_GREEN(s)   "\033[32;1m" s "\033[0m"

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++; \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            count_fail++; \
        } \
    } while (0)

#endif
