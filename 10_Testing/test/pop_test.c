#include <stdio.h>
#include <stdint.h>

#include "buf.h"

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

int
main(int argc, char **argv)
{
    volatile int count_pass = 0;
    volatile int count_fail = 0;
    float *a = 0;

    /* buf_pop() */
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    TEST("size 4", buf_size(a) == 4);
    TEST("pop 3", buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    TEST("size 3", buf_size(a) == 3);
    TEST("pop 2", buf_pop(a) == (float)1.3f);
    TEST("pop 1", buf_pop(a) == (float)1.2f);
    TEST("pop 0", buf_pop(a) == (float)1.1f);
    TEST("size 0 (pop)", buf_size(a) == 0);
    buf_free(a);

    printf("%d fail, %d pass\n", count_fail, count_pass);
    return count_fail != 0;
}
