#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"


int random_walker_solver(int verbose, maze_t *maze, walker_t *walker) {
    int random = rand();
    int dir = random % 4;
    if (verbose) fprintf(stdout, "random: %d\n", random);
    if (verbose) fprintf(stdout, "dir: %d\n", dir);
    return dir;
}

/* Next super solver here.. */
