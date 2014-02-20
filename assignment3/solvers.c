#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"


int random_walker_solver(int verbose, maze_t *maze, walker_t *walker) {
    /* srand(time(NULL)); */
    int dir = abs(rand() % 4);
    if (verbose) fprintf(stdout, "Direction: %d", dir);
    return dir;
}

/* Next super solver here.. */
