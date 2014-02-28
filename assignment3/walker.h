#ifndef WALKER_H
#define WALKER_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL  '#'
#define START 'S'
#define EXIT  'E'

/*
 * Struct for the walker type containing the location in row and col
 * Also saves the last move it done
 */
typedef struct {
    int col;
    int row;
    int last_move;
} walker_t;


/*
 * init_walker()
 * -------------
 * Initialize an walker with enough space and find het starting position in the maze.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @return; An initizalized walker structure.
 */
walker_t* init_walker(int verbose, maze_t* maze );

/*
 * at_exit()
 * -------------
 * Tests if the walker is at the (E)xit of the maze.
 *
 * @param maze; pointer to a maze structure.
 * @param walker; pointer to a walker structure.
 * @return; true or false.
 */
int at_exit(maze_t* maze, walker_t* walker);

/*
 * check_move()
 * -------------
 * Tests if the move in given direction is valid.
 *
 * @param verbose; flag for more printing more information.
 * @param maze; pointer to a maze structure.
 * @param walker; pointer to a walker structure.
 * @param direction; direction to test.
 * @return; true or false.
 */
int check_move(int verbose, maze_t* maze, walker_t* walker, int direction);

/*
 * move_walker()
 * -------------
 *
 * @param verbose; flag for more printing more information.
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @param direction; the direction to move the walker in.
 * @return; result boolean based on succes.
 */
int move_walker(int verbose, maze_t* maze, walker_t* walker, int direction);

/*
 * cleanup_walker()
 * ----------------
 * Free the memory used by the given walker structure.
 *
 * @param walker; pointer to the walker structure.
 * @return; void.
 */
void cleanup_walker(walker_t* walker);

#endif /* WALKER_H */
