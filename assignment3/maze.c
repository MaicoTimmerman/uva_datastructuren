#include <stdio.h>
#include <stdlib.h>

#include "maze.h"

maze_t* init_maze(int verbose, maze_t *maze, int x_maze, int y_maze) {

    maze = malloc(sizeof(maze_t));
    maze->map = malloc(y_maze * sizeof(char*));
    for (int i = 0; i < y_maze; i++) {
        maze->map[i] = malloc(x_maze * sizeof(char));
    }
    return maze;
}

maze_t* read_maze(int verbose, maze_t *maze, char *maze_file_path ) {

    int x_maze, y_maze;
    FILE *fp = NULL;

    fp = fopen(maze_file_path, "r");

    if(!fp) {
        perror(maze_file_path);
        return 0;
    }

    /* Get the dimensions of the maze map from the first line. */
    if (fscanf(fp, "%d, %d", &x_maze, &y_maze) == 2 ) {
        if (verbose)
            fprintf(stdout, "Maze dimensions: x: %d, y: %d\n", x_maze, y_maze);
    }

    /* Allocate memory regarding the size of the maze */
    maze = init_maze(verbose, maze, x_maze, y_maze);

    for (int i = 0; i < y_maze; i++) {
        for (int j = 0; j < x_maze; j++) {
            if ((maze->map[i][j] = fgetc(fp)) == EOF) {
                if (feof(fp) && verbose) {
                    fprintf(stdout, "End of file reached\n");
                }
                if (ferror(fp) && verbose) {
                    fprintf(stdout, "An error happened\n");
                }
            }
        }
    }
    fclose(fp);
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
        for (int i = 0; i < maze->row; i++) {
            if (maze->map[i]) {
                free(maze->map[i]);
                maze->map[i] = NULL;
            }
        }
        free(maze->map);
        maze->map = NULL;
    }
    free(maze);
}
