#include <stdio.h>
#include <stdlib.h>

#include "maze.h"

maze_t* init_maze(int verbose, maze_t *maze, int x_maze, int y_maze) {

    maze = malloc(sizeof(maze_t));
    maze->map = malloc(y_maze * (x_maze + 1) * sizeof(char));
    return maze;
}

maze_t* read_maze(int verbose, maze_t *maze, char *maze_file_path ) {

    int x_maze, y_maze;
    char ch;
    FILE *fp = NULL;

    fp = fopen(maze_file_path, "r");

    if(!fp) {
        perror(maze_file_path);
        return 0;
    }

    /* Get the dimensions of the maze map from the first line. */
    if (fscanf(fp, "%d, %d", &x_maze, &y_maze) == 2 ) {
        if (verbose)
            fprintf(stdout, "Maze dimensions: x: %d, y: %d", x_maze, y_maze);
    }

    /* Allocate memory regarding the size of the maze */
    maze = init_maze(verbose, maze, x_maze, y_maze);

    for (int i = 0; i < y_maze; i++) {
        fgets(maze->map[i], (x_maze + 1), fp);
    }
    return maze;

}

void print_maze(int verbose, maze_t *maze, int row_walker, int col_walker ) {
    for (int i = 0; i < maze->row; i++) {
        for (int j = 0; j < maze->col; j++) {
            if ((i == row_walker) && (j == col_walker)) {
                putchar('X');
            }
            putchar(maze->map[i][j]);
        }
    }
}

void cleanup_maze (maze_t *maze) {
    if (maze->map) {
        free(maze->map);
        maze->map = NULL;
    }
    free(maze);
}
