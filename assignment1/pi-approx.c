#include <stdlib.h>
#include <stdio.h>
/* For INT_MIN and INT_MAX */
#include <limits.h>
/* For sqrt() */
#include <math.h>
/* For time() */
#include <time.h>

#define ARGS_REQUIRED 2
#define CIRCLE_RANGE 1.0

/* Print the usage of this program */
int help() {
    printf("Usage: pi [iterations]\n");
    printf("  iterations: [int] used to calculate pi\n");
    printf("    where: [int] <  %d\n", INT_MAX);
    printf("    where: [int] > %d\n", INT_MIN);
    return 1;
    exit(EXIT_FAILURE);
}

/* Test if the point had a diagonal < 1 using Pythagoras */
int testInsideCircle(double x, double y) {
    double rsquare = ((x*x) + (y*y));
    double r = sqrtf(rsquare);
    if ( r < CIRCLE_RANGE ) {
        return 1;
    } else {
        return 0;
    }
}

/* Calculate pi from the ratio of point in- and outside the circle */
double calcPi(int insideCircle, int iterations) {
    return 4 * ((double)insideCircle / (double)iterations);
}

int main(int argc, char *argv[]) {
    if (argc < ARGS_REQUIRED ) {
        return help();
    } else if (atoi(argv[1]) > INT_MAX || atoi(argv[1]) < 1) {
        return help();
    }

    int i;
    double x, y;
    int inside;
    int iterations = atoi(argv[1]);
    int insideCircle = 0;
    srand(time(NULL));

    /* Get a new point and test if inside the circle.
     * Add one to the matching value */
    for (i = 0; i < iterations; i++) {
        /* Get new random coords */
        x = (double)rand()/(double)RAND_MAX;
        y = (double)rand()/(double)RAND_MAX;

        /* Test if coords are inside circle  */
        inside = testInsideCircle(x,y);
        if ( inside ) {
            insideCircle++;
        }
    }

    double pi = calcPi((double)insideCircle, (double)iterations);
    printf("Pi equals: ~%f, calculation done with %d iterations\n", pi, iterations);
    exit(EXIT_SUCCESS);
}
