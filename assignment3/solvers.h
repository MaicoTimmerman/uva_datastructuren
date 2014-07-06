#ifndef SOLVERS_H
#define SOLVERS_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL  '#'
#define START 'S'
#define EXIT  'E'

/*
 * random_walker_solver()
 * ----------------------
 * Algorithm for solving a maze using random directions.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @return; direction the make the next move.
 */
int random_walker_solver(int verbose, maze_t *maze, walker_t *walker);

/*
 * wall_follow_solver()
 * ----------------------
 * Algorithm for solving a maze using the wall following method.
 *
 * @param maze; pointer to a maze structure where the walker is placed in.
 * @param walker; pointer to the walker structure.
 * @return; direction the make the next move.
 */
int wall_follow_solver(int verbose, maze_t *maze, walker_t *walker);
#endif /* SOLVERS_H */
