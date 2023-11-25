#include "test_utils.h"
#include "buf.h"

int
main(int argc, char **argv)
{
    volatile int count_pass = 0;
    volatile int count_fail = 0;
    float *a = 0;

    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);
    TEST("clear empty", buf_size(a) == 0);
    TEST("clear no-op", a == 0);
    return 0;
}
