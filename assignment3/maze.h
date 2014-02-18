/* Contains function related to the maze map of the game. */
#ifndef MAZE_H
#define MAZE_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL    '#'
#define START   'S'
#define EXIT    'E'

/*
 * Structure of the maze containing the maze layout in a 2D array,
 * the width and the height.
 * The first pointer points to the rows and then second to the chars in the rows.
 */
typedef struct {
    char **map;
    int row;
    int col;
} maze_t;


/* Incomplete declarations of the support functions. */
maze_t* init_maze(int verbose, maze_t *maze, int x_maze, int y_maze);
maze_t* read_maze(int verbose, maze_t *maze, char *maze_file_path );
void print_maze(int verbose, maze_t *maze, int row_walker, int col_walker );
void cleanup_maze (maze_t *maze);

#endif /* MAZE_H */
