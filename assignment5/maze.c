#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

/* Allocate and initialise a maze of size nrows x ncols.
 * Use: maze->map[row][col]
 */
maze_t* init_maze(int nrows, int ncols) {
    int r;

    maze_t* maze = malloc(sizeof (maze_t));
    assert(maze);
    maze->nrows = nrows;
    maze->ncols = ncols;
    maze->map = malloc(sizeof(char*) * maze->nrows);
    assert(maze->map);
    for (r = 0; r < nrows; r++) {
        maze->map[r] = malloc(sizeof(char) * maze->ncols);
        assert(maze->map[r]);
    }
    return maze;
}


/* Check if map symbol is valid.
 * If edge is true, symbol needs to be WALL.
 */
void check_symbol(char c, int edge) {
    switch (c) {
        case WALL:
            break;
        case START:
        case EXIT:
        case OPEN:
            if (!edge)
                break;
            // fall thru if it's an edge
        default:
            if (c == '\n')
                printf("Newline is not allowed in the maze\n");
            else
                printf("Invalid map symbol: '%c'%s\n", c,
                        edge?" at edge of maze":"");
            exit(2);
    }
}


/* Read maze from file. */
maze_t* read_maze(char* filename) {

    int row, col, n;
    int nrows, ncols;
    FILE* infile;
    maze_t* maze;

    if ((infile = fopen(filename, "r")) == NULL) {
        perror("Error opening file");
        exit(2);
    }

    /* Read header. */
    n = fscanf(infile, "%d,%d\n", &nrows, &ncols);
    assert(n == 2);
    maze = init_maze(nrows, ncols);

    /* Read ascii map. */
    for (row = 0; row < maze->nrows; row++) {
        for (col = 0; col < maze->ncols - 1; col++) { // exclude last (newline '\n')
            n = fscanf(infile, "%c", &(maze->map[row][col]));
            assert (n == 1);
            check_symbol(maze->map[row][col], (row == 0) ||
                                              (row == maze->nrows-1) ||
                                              (col == 0) );
            if (maze->map[row][col] == START) {
                maze->start_row = row;
                maze->start_col = col;
            }
            if (maze->map[row][col] == EXIT) {
                maze->end_row = row;
                maze->end_col = col;
            }
        }
        // Now read last entry of row (newline '\n')
        n = fscanf(infile, "%c\n",
                &(maze->map[row][col]));
        assert (n == 1);
        check_symbol(maze->map[row][col], 1);
    }
    fclose(infile);
    return maze;
}

/* Print maze. Will mark the position p_row,p_col
 * with an 'x'.
 */
void print_maze(maze_t* maze, int p_row, int p_col) {
    int row, col;

    for (row = 0; row < maze->nrows; row++) {
        for (col = 0; col < maze->ncols; col++) {
            if (p_col == col && p_row == row)
                printf("x");
            else
                printf("%c", maze->map[row][col]);
        }
        printf("\n");
    }
}

/* Free maze data. */
void cleanup_maze(maze_t* m) {
    int r;

    for (r = 0; r < m->nrows; r++)
        free(m->map[r]);
    free(m->map);
    free(m);
}
