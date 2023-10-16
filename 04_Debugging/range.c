#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct range {
    int begin;
    int end;
    int step;
    int current;
} range;

void argparse(int argc, char *argv[], int *begin, int *end, int *step) {
    if (argc == 1) {
        fputs("Usage:\n", stderr);
        fputs("\t./range <end> -- iterate over [0; <end>)\n", stderr);
        fputs("\t./range <begin> <end> -- iterate over [<begin>; <end>)\n", stderr);
        fputs("\t./range <begin> <end> <step> -- iterate over [<begin>; <end>) with step <step>\n",
              stderr);
        exit(1);
    }
    if (argc == 2) {
        *begin = 0;
        *end = atoi(argv[1]);
        *step = 1;
        return;
    }
    if (argc == 3) {
        *begin = atoi(argv[1]);
        *end = atoi(argv[2]);
        *step = 1;
        return;
    }
    *begin = atoi(argv[1]);
    *end = atoi(argv[2]);
    *step = atoi(argv[3]);
}

void range_init(range *iter) {
    iter->current = iter->begin;
}

bool range_run(range *iter) {
    return (iter->step > 0 && iter->current < iter->end) ||
           (iter->step < 0 && iter->current > iter->end);
}

int range_next(range *iter) {
    return iter->current += iter->step;
}

int range_get(range *iter) {
    return iter->current;
}

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.begin, &I.end, &I.step);
    for (range_init(&I); range_run(&I); range_next(&I))
        printf("%d\n", range_get(&I));
    return 0;
}
