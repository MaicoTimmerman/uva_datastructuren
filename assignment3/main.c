#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"
#include "main.h"

int verbose = 0;

int main (int argc, char **argv) {

    maze_t* maze = NULL;
    walker_t* walker = NULL;
    int count;
    int dir;
    int solver = -1;
    char maze_file_path[MAX_FILE_PATH_LEN] = "";

    /* Read all the command line parameters */
    if (!get_args(argc, argv, maze_file_path, &solver)) {
        fprintf(stderr, "maze-solver: try 'maze-solver -h' for more information.\n");
        return EXIT_FAILURE;
    }

    /* Initialize and read the maze */
    if ((maze = read_maze(verbose, maze_file_path)) == NULL) {
        fprintf(stderr, "maze-solver: could not initialize maze.\n");
        return EXIT_FAILURE;
    }

    /* Initialize the walker */
    if ((walker = init_walker(verbose, maze)) == NULL) {
        fprintf(stderr, "maze-solver: could not initialize walker.\n");
        return EXIT_FAILURE;
    }

    if (verbose)fprintf(stdout, "maze-solver: Maze succesfully read.\n");

    /* check your args, read maze here, init walker.. */

    count = 0;
    srand(time(NULL));

    /*
     * Print the maze step by step with the correct solver algorithm.
     */
    while (count++ < MAX_STEPS) {
        switch (solver) {
            case WALL_FOLLOWER:
                dir = wall_follow_solver(verbose, maze, walker);
                break;
            case RANDOM_WALKER:
                dir = random_walker_solver(verbose, maze, walker);
                break;
        }
        move_walker(verbose, maze, walker, dir);
        print_maze(verbose, maze, walker->row, walker->col);
        printf("Moves: %d\n", count);
        if (at_exit(maze, walker))
            break;
    }

    if (count < MAX_STEPS)
        printf("Found exit after %d steps\n", count);

    cleanup_maze(maze);
    cleanup_walker(walker);


    return EXIT_SUCCESS;

}

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
int get_args(int argc, char **argv, char *maze_file_path, int *solver) {

    int opt;
    extern char *optarg;
    extern int optind, optopt;

    /* Get all options from the command line */
    while ((opt = getopt(argc, argv, "vhm:s:")) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            case 'h':
                help();
                break;
            case 'm':
                if (optarg && (strlen(optarg) < MAX_FILE_PATH_LEN)) {
                    strcpy(maze_file_path, optarg);
                }
                break;
            case 's':
                if (atoi(optarg) == WALL_FOLLOWER)
                    *solver = WALL_FOLLOWER;
                else if (atoi(optarg) == RANDOM_WALKER)
                    *solver = RANDOM_WALKER;
                else
                    *solver = -1;
                break;
        }
    }

    /* If no frequency file is found */
    if (maze_file_path[0] == '\0') {
        fprintf(stderr, "maze-solver: specify a maze file path with [-m](maximum path length is 60 characters)\n");
        return 0;
    }

    /* If solver is not found */
    if (*solver == -1) {
        fprintf(stdout, "maze-solver: cannot determine solver, specify solver with [-s]\n");
        return 0;
    }

    if (verbose)
        printf("maze_file_path\t = %s\n", maze_file_path);

    return 1;
}

/*
 * Function: help()
 * ----------------
 * Print the usage of this program
 *
 * @returns succes after printing the help of this program
 */
void help(void) {
    printf("Usage: maze-solver [ -v | -h ] [ -m mazefile ] [ -s solver ]\n");
    printf("Obligatory: [ -m mazefile ] [ -s solver ]\n");
    printf("Example: maze-solver -m mapDir/map1.txt\n\n");
    printf("    -m filepath  filepath to a file containing the maze file.\n");
    printf("    -s solver    index of the solver used for the maze.\n");
    printf("                 solver 1: random maze solver\n");
    printf("                 solver 2: wall follow maze solver\n");
    printf("    -v           verbose: print more details.\n");
    printf("    -h           help: print this help page.\n");
    exit(EXIT_SUCCESS);
}
