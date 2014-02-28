#include<stdio.h>
#include<stdlib.h>

#include "maze.h"
#include "walker.h"

/*
 * init_walker()
 * -------------
 * Initialize an walker with enough space and find het starting position in the maze.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @return; An initizalized walker structure.
 */
walker_t* init_walker(int verbose, maze_t* maze ) {

    walker_t* walker = (walker_t*)malloc(sizeof(walker_t));

    /* Find the start of the maze */
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if (maze->map[i][j] == 'S') {
                walker->row = i;
                walker->col = j;
                walker->last_move = -1;
                if (verbose) {
                    fprintf(stdout, "The starting position is at %d,%d\n", i, j);
                }
                return walker;
            }
        }
    }
    return NULL;
}

/*
 * at_exit()
 * -------------
 * Tests if the walker is at the (E)xit of the maze.
 *
 * @param maze; pointer to a maze structure.
 * @param walker; pointer to a walker structure.
 * @return; true or false.
 */
int at_exit(maze_t* maze, walker_t* walker) {
    return (maze->map[walker->row][walker->col] == 'E') ? 1 : 0;
}

/*
 * check_move()
 * -------------
 * Tests if the move in given direction is valid.
 *
 * @param verbose; flag for more printing more information.
 * @param maze; pointer to a maze structure.
 * @param walker; pointer to a walker structure.
 * @param direction; direction to test.
 * @return; true or false.
 */
int check_move(int verbose, maze_t* maze, walker_t* walker, int direction) {
    switch (direction) {
        case NORTH:
            if (maze->map[walker->row-1][walker->col] != WALL) {
                if (verbose) fprintf(stdout, "NORTH != WALL\n");
                return 1;
            }
            break;
        case EAST:
            if (maze->map[walker->row][walker->col+1] != WALL) {
                if (verbose) fprintf(stdout, "EAST != WALL\n");
                return 1;
            }
            break;
        case SOUTH:
            if (maze->map[walker->row+1][walker->col] != WALL) {
                if (verbose) fprintf(stdout, "SOUTH != WALL\n");
                return 1;
            }
            break;
        case WEST:
            if (maze->map[walker->row][walker->col-1] != WALL) {
                if (verbose) fprintf(stdout, "WEST != WALL\n");
                return 1;
            }
            break;
        default:
            return 0;
    }
    return 0;
}

/*
 * move_walker()
 * -------------
 *
 * @param verbose; flag for more printing more information.
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @param direction; the direction to move the walker in.
 * @return; result boolean based on succes.
 */
int move_walker(int verbose, maze_t* maze, walker_t* walker, int direction) {
    maze->map[walker->row][walker->col] = '.';
    switch (direction) {
        case NORTH:
            if (check_move(verbose, maze, walker, direction)) {
                if (verbose) fprintf(stdout, "Walker moving: North\n");
                walker->row -= 1;
                walker->last_move = direction;
                return 1;
            }
            break;
        case EAST:
            if (check_move(verbose, maze, walker, direction)) {
                if (verbose) fprintf(stdout, "Walker moving: East\n");
                walker->col += 1;
                walker->last_move = direction;
                return 1;
            }
            break;
        case SOUTH:
            if (check_move(verbose, maze, walker, direction)) {
                if (verbose) fprintf(stdout, "Walker moving: South\n");
                walker->row += 1;
                walker->last_move = direction;
                return 1;
            }
            break;
        case WEST:
            if (check_move(verbose, maze, walker, direction)) {
                if (verbose) fprintf(stdout, "Walker moving: West\n");
                walker->col -= 1;
                walker->last_move = direction;
                return 1;
            }
            break;
        default:
            return 0;
    }
    return 0;
}

/*
 * cleanup_walker()
 * ----------------
 * Free the memory used by the given walker structure.
 *
 * @param walker; pointer to the walker structure.
 * @return; void.
 */
void cleanup_walker(walker_t* walker) {
    free(walker);
    walker = NULL;
}
