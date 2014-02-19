#include<stdio.h>
#include<stdlib.h>

#include "maze.h"
#include "walker.h"

walker_t* init_walker(int verbose, maze_t* maze ) {

    walker_t* walker = (walker_t*)malloc(sizeof(walker_t));

    /* Find the start of the maze */
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if (maze->map[i][j] == 'S') {
                walker->row = i;
                walker->col = j;
                return walker;
            }
        }
    }
}

int at_exit(int verbose, maze_t* maze, walker_t* walker) {
    return 0;
}

int check_move(int verbose, maze_t* maze, walker_t* walker, int direction) {
    return 1;
}

int move_walker(int verbose, maze_t* maze, walker_t* walker, int direction) {
    return 1;
}

void cleanup_walker(walker_t* walker) {
    free(walker);
}
