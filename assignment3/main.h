#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#define MAX_STEPS 10000
#define MAX_FILE_PATH_LEN 64

int get_args(int argc, char **argv, char *maze_file_path);

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
void help(void);

#endif /* MAZE_SOLVER_H */
