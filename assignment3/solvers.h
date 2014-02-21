#ifndef SOLVERS_H
#define SOLVERS_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL  '#'
#define START 'S'
#define EXIT  'E'

/* Solver function that will return a random direction for the next step. */
int random_walker_solver(int verbose, maze_t *maze, walker_t *walker);
int wall_follow_solver(int verbose, maze_t *maze, walker_t *walker);
#endif
