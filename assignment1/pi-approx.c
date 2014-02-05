/*
 * File: pi-approx.c
 *
 * This file implements a program that calculates an estimate
 * value of by with an simple algorithm.
 * The number of iterations used for the program affects
 * the significance of the calculated pi to the real pi
 *
 * @author: Maico Timmerman
 * @uvanetid: 10542590
 * @date: 04 Feb 2014
 * @version: 0.1
 *
 */

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

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
int help() {
    printf("Usage: pi [iterations]\n");
    printf("  iterations: [int] used to calculate pi\n");
    printf("    where: [int] <  %d\n", INT_MAX);
    printf("    where: [int] > 0\n");
    return EXIT_SUCCESS;
}

/*
 * Function: testinsideCircle(x,y)
 * -------------------------------
 * Test if the point had a diagonal < 1 using Pythagoras
 *
 * @param x; x-coordinate of the point.
 * @param y; y-coordinate of the point.
 * @return boolean if the point is inside the unitcircle
 */
int testInsideCircle(double x, double y) {
    double rsquare = ((x*x) + (y*y));
    double r = sqrtf(rsquare);
    if ( r < CIRCLE_RANGE ) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Function: calcPi(insideCircle, iterations)
 * ------------------------------------------
 * Calculate pi from the ratio of point in- and outside the circle
 *
 * @param insideCircle; amount of points inside the unitcircle
 * @param iterations; total amount of random points taken.
 * @return an estimated value of pi
 */
double calcPi(int insideCircle, int iterations) {
    return 4 * ((double)insideCircle / (double)iterations);
}

/*
 * Main program for calculating pi
 *
 * @param argc; number of parameters given to the program
 * @param argv; array of all parameters given to the program
 */
int main(int argc, char *argv[]) {
    /* Check if sufficient arguments are given */
    if (argc < ARGS_REQUIRED ) {
        return help();
    } else if (atoi(argv[1]) > INT_MAX || atoi(argv[1]) < 1) {
        return help();
    }

    double x, y;
    int iterations = atoi(argv[1]);
    int insideCircle = 0;
    srand(time(NULL));

    /* Get a new point and test if inside the unitcircle for every iteration.
     * add one to the matching value, if inside the unitcircle*/
    int i;
    for (i = 0; i < iterations; i++) {
        /* Get new random coords */
        x = (double)rand()/(double)RAND_MAX;
        y = (double)rand()/(double)RAND_MAX;

        /* Test if coords are inside unitcircle  */
        if ( testInsideCircle(x,y) ) {
            insideCircle++;
        }
    }

    /* Calculate pi and print the results */
    double pi = calcPi((double)insideCircle, (double)iterations);
    printf("Pi equals: ~%f, calculation done with %d iterations\n", pi, iterations);
    return EXIT_SUCCESS;
}
