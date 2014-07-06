#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#define MAX_STEPS 100000
#define MAX_FILE_PATH_LEN 64

#define WALL_FOLLOWER 1
#define RANDOM_WALKER 2

/*
 * Function: get_args()
 * -------------------
 * Get all the arguments from the command line and place them in the given parameters.
 *
 * @param argc; number of commandline parameters.
 * @param argv; array of commandline parameters with length argc.
 * @param maze_file_path; location for the filepath to the maze file.
 * @param solver; value for which solver to use.
 * @returns; Succes after printing the help of this program.
 */
int get_args(int argc, char **argv, char *maze_file_path, int *solver);

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
void help(void);

#endif /* MAZE_SOLVER_H */
