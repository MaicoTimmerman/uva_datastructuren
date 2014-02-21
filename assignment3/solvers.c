#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"


int random_walker_solver(int verbose, maze_t *maze, walker_t *walker) {
    int dir;
    do {
        dir = rand() % 4;
    } while (!check_move(maze, walker, dir));

    if (verbose) fprintf(stdout, "dir: %d\n", dir);
    return dir;
}


int wall_follow_solver(int verbose, maze_t *maze, walker_t *walker) {
    /*
     * Direction array with index linked to direction depending on last direction:
     * left = dir[0]
     * straight = dir[1]
     * right = dir[2]
     * backwards = dir[3]
     */
    int dir[4];
    switch (walker->last_move) {
        case NORTH:
            dir[0] = WEST;
            dir[1] = NORTH;
            dir[2] = EAST;
            dir[3] = SOUTH;
            break;
        case EAST: break;
            dir[0] = NORTH;
            dir[1] = EAST;
            dir[2] = SOUTH;
            dir[3] = WEST;
            break;
        case SOUTH: break;
            dir[0] = EAST;
            dir[1] = SOUTH;
            dir[2] = WEST;
            dir[3] = NORTH;
            break;
        case WEST: break;
            dir[0] = SOUTH;
            dir[1] = WEST;
            dir[2] = NORTH;
            dir[3] = EAST;
            break;
    }
    for (int i = 0; i < 4; i++) {
        if (check_move(maze, walker, dir[i])) {
            if (verbose) fprintf(stdout, "dir: %d\n", dir[i]);
            return dir[i];
        }
    }

    return dir[0];
}
