#include <stdio.h>
#include <stdlib.h>

#include "maze.h"

/*
 * init_maze()
 * -----------
 * Initialize a maze structure with the given dimensions.
 *
 * @param verbose; flag for more printing more information.
 * @param x_maze; width of the maze.
 * @param y_maze; height of the maze.
 * @return; an initialized maze structure with allocated memory.
 */
maze_t* init_maze(int verbose, int x_maze, int y_maze) {

    maze_t* maze = (maze_t*)malloc(sizeof(maze_t));

    maze->rows = y_maze;
    maze->cols = x_maze;

    maze->map = (char**)malloc(y_maze * sizeof(char *));
    if (verbose)
        fprintf(stdout, "maze->map = %p\n", (void *)maze->map);

    for (int i = 0; i < y_maze; i++) {
        maze->map[i] = (char*)malloc(x_maze * sizeof(char));
        if (verbose)
            fprintf(stdout, "maze->map[%d] = %p\n",i , (void *)maze->map[i]);
    }
    return maze;
}

/*
 * read_maze()
 * -----------
 * Read a maze from a given file.
 *
 * @param verbose; flag for more printing more information.
 * @param maze_file_path; file path to an file with an maze.
 * @return; an filled maze structure with the data from the file located at maze_file_path.
 */
maze_t* read_maze(int verbose, char *maze_file_path ) {

    int x_maze, y_maze;
    char ch;
    FILE *fp = NULL;
    maze_t *maze = NULL;

    fp = fopen(maze_file_path, "r");

    if(!fp) {
        perror(maze_file_path);
        return 0;
    }

    /* Get the dimensions of the maze map from the first line. */
    if (fscanf(fp, "%d, %d\n", &y_maze, &x_maze) == 2 ) {
        if (verbose)
            fprintf(stdout, "Maze dimensions: x: %d, y: %d\n", x_maze, y_maze);
    }

    /* Allocate memory regarding the size of the maze */
    maze = init_maze(verbose, x_maze, y_maze);
    if (verbose)
        fprintf(stdout, "maze pointer: %p\n", (void *)maze);

    for (int i = 0; i < y_maze; i++) {
        for (int j = 0; j < x_maze; j++) {
            if ((ch = fgetc(fp)) == EOF) {
                if (feof(fp) && verbose) {
                    fprintf(stdout, "\nEnd of file reached\n");
                }
                if (ferror(fp) && verbose) {
                    fprintf(stdout, "\nAn error happened\n");
                    return NULL;
                }
            }
            maze->map[i][j] = ch;
            if (verbose)
                putchar(ch);
        }
        /* Keep in mind the file had newlines */
        fseek(fp, 1, SEEK_CUR);
        if (verbose)
            putchar('\n');
    }
    if (verbose)
        fprintf(stdout, "\n\nMaze read done!\n");
    fclose(fp);
    return maze;

}

/*
 * print_maze()
 * ------------
 * Prints the maze from the given maze structure.
 * The location of the walker is representened with X.
 *
 * @param verbose; flag for more printing more information.
 * @param row_walker; the row the walker is located on.
 * @param col_walker; the column the walker is located on.
 * @return; void.
 */
void print_maze(int verbose, maze_t *maze, int row_walker, int col_walker ) {
    if (verbose) fprintf(stdout, "Walker at row: %d, col: %d!\n", row_walker, col_walker);

    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            if ((i == row_walker) && (j == col_walker)) {
                putchar('X');
            } else {
                putchar(maze->map[i][j]);
            }
        }
        putchar('\n');
    }
}

/*
 * cleanup_maze()
 * --------------
 * Free all memory used by the structure.
 *
 * @param maze; pointer to a maze structure.
 * @return; void.
 */
void cleanup_maze(maze_t *maze) {
    if (maze->map) {
        for (int i = 0; i < maze->rows; i++) {
            if (maze->map[i]) {
                free(maze->map[i]);
                maze->map[i] = NULL;
            }
        }
        free(maze->map);
        maze->map = NULL;
    }
    free(maze);
    maze = NULL;
}
