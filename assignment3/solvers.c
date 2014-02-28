#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"


/*
 * random_walker_solver()
 * ----------------------
 * Algorithm for solving a maze using random directions.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @return; direction the make the next move.
 */
int random_walker_solver(int verbose, maze_t *maze, walker_t *walker) {
    int dir;
    do {
        dir = rand() % 4;
    } while (!check_move(verbose, maze, walker, dir));

    if (verbose) fprintf(stdout, "Dir from solver: %d\n", dir);
    return dir;
}

/*
 * wall_follow_solver()
 * ----------------------
 * Algorithm for solving a maze using the wall following method.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @return; direction the make the next move.
 */
int wall_follow_solver(int verbose, maze_t *maze, walker_t *walker) {
    /*
     * Direction array with index linked to direction depending on last direction:
     * left = dir[0]
     * straight = dir[1]
     * right = dir[2]
     * backwards = dir[3]
     */
    int dir[4];
    int direction;
    int return_value;
    if (verbose) fprintf(stdout, "walker->lastmove: %d\n", walker->last_move);
    switch (walker->last_move) {
        case NORTH:
            dir[0] = WEST, dir[1] = NORTH, dir[2] = EAST, dir[3] = SOUTH;
            break;
        case EAST:
            dir[0] = NORTH, dir[1] = EAST, dir[2] = SOUTH, dir[3] = WEST;
            break;
        case SOUTH:
            dir[0] = EAST, dir[1] = SOUTH, dir[2] = WEST, dir[3] = NORTH;
            break;
        case WEST:
            dir[0] = SOUTH, dir[1] = WEST, dir[2] = NORTH, dir[3] = EAST;
            break;
        case -1:
            while (1) {
                direction = rand() % 4;
                if (check_move(verbose, maze, walker, direction)) {
                    return_value = direction;
                    break;
                }
            }

    }

    for (int i = 0; i < 4; i++) {
        if (check_move(verbose, maze, walker, dir[i])) {
            if (verbose) fprintf(stdout, "Dir from solver: %d\n", dir[i]);
            return_value = dir[i];
            break;
        }
    }
    return return_value;
}
