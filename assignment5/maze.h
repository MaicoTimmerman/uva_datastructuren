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
#define OPEN    ' '

#define PATH    '.'

typedef struct {
    char** map; // use as map[row][col]
    int nrows;
    int ncols;
    int start_row, start_col;
    int end_row, end_col;
} maze_t;


maze_t* init_maze(int nrows, int ncols);
maze_t* read_maze(char* filename);
void print_maze(maze_t* maze, int p_row, int p_col);
void cleanup_maze(maze_t* m);

#endif /* MAZE_H */
