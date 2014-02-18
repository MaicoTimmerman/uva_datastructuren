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
 */
typedef struct {
    char **map;
    int x;
    int y;
} maze_t;


/* Incomplete declarations of the support functions. */
maze_t* init_maze( ... );
maze_t* read_maze( ... );
void print_maze( ... );
void cleanup_maze ( ... );

#endif
