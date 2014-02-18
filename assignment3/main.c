#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"

#define MAX_STEPS 10000
#define MAX_FILE_PATH_LEN 64

int verbose = 0;

int main (int argc, char **argv) {

    maze_t* maze;
    walker_t* walker;
    int count;
    int dir;
    char mazeFilePath[MAX_FILE_PATH_LEN] = "";

    /* check your args, read maze here, init walker.. */
    if (!getArgs(argc, argv, mazeFilePath)) {
        fprintf(stderr, "maze-solver: try 'maze-solver -h' for more information.\n");
        return EXIT_FAILURE;
    }

    count = 0;
    while (count++ < MAX_STEPS) {
        dir = my_super_maze_solver_function(maze, walker);
        move_walker(maze, walker, dir);
        print_maze(maze, walker->row, walker->col);
        printf("Moves: %d\n", count);
        if (at_exit(maze, walker))
            break;
    }

    if (count < MAX_STEPS)
        printf("Found exit after %d steps\n", count);


    return 0;

}
