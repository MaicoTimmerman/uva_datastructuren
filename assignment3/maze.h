/* Contains function related to the maze map of the game. */
#ifndef MAZE_H
#define MAZE_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL  '#'
#define START 'S'
#define EXIT  'E'

/*
 * Structure of the maze containing the maze layout in a 2D array,
 * the width and the height.
 * The first pointer points to the rows and then second to the chars in the rows.
 */
typedef struct {
    char **map;
    int rows;
    int cols;
} maze_t;


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
maze_t* init_maze(int verbose, int x_maze, int y_maze);

/*
 * read_maze()
 * -----------
 * Read a maze from a given file.
 *
 * @param verbose; flag for more printing more information.
 * @param maze_file_path; file path to an file with an maze.
 * @return; an filled maze structure with the data from the file located at maze_file_path.
 */
maze_t* read_maze(int verbose, char *maze_file_path );

/*
 * print_maze()
 * -----------
 * Prints the maze from the given maze structure.
 * The location of the walker is representened with X.
 *
 * @param verbose; flag for more printing more information.
 * @param row_walker; the row the walker is located on.
 * @param col_walker; the column the walker is located on.
 * @return; void.
 */
void print_maze(int verbose, maze_t *maze, int row_walker, int col_walker );

/*
 * cleanup_maze()
 * --------------
 * Free all memory used by the structure.
 *
 * @param maze; pointer to a maze structure.
 * @return; void.
 */
void cleanup_maze(maze_t *maze);

#endif /* MAZE_H */
