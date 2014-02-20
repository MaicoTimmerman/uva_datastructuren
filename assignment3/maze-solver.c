#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#include "maze.h"
#include "walker.h"
#include "solvers.h"
#include "maze-solver.h"

int verbose = 0;

int main (int argc, char **argv) {

    maze_t* maze = NULL;
    walker_t* walker = NULL;
    int count;
    int dir;
    char maze_file_path[MAX_FILE_PATH_LEN] = "";

    /* Read all the command line parameters */
    if (!get_args(argc, argv, maze_file_path)) {
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

    if (verbose)
        fprintf(stdout, "maze-solver: Maze succesfully read.\n");


    /* check your args, read maze here, init walker.. */

    count = 0;
    srand(time(NULL));
    while (count++ < MAX_STEPS) {
        dir = random_walker_solver(verbose, maze, walker);
        move_walker(verbose, maze, walker, dir);
        print_maze(verbose, maze, walker->row, walker->col);
        printf("Moves: %d\n", count);
        if (at_exit(verbose, maze, walker))
            break;
    }

    if (count < MAX_STEPS)
        printf("Found exit after %d steps\n", count);

    cleanup_maze(maze);
    maze = NULL;
    cleanup_walker(walker);
    walker = NULL;


    return EXIT_SUCCESS;

}

int get_args(int argc, char **argv, char *maze_file_path) {

    int opt;
    extern char *optarg;
    extern int optind, optopt;

    /* Get all options from the command line */
    while ((opt = getopt(argc, argv, "vhm:")) != -1) {
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
        }
    }

    /* If no frequency file is found */
    if (maze_file_path[0] == '\0') {
        fprintf(stderr, "Error: specify a maze file path with [-m](maximum path length is 60 characters)\n");
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
    printf("Usage: maze-solver [ -v | -h ] [ -m mazefile ]\n");
    printf("Obligatory: [ -m mazefile ]\n");
    printf("Example: maze-solver -m mapDir/map1.txt\n\n");
    printf("\t-m filepath\t filepath to a file containing the maze file.\n");
    printf("\t-v\t\t verbose: print more details.\n");
    printf("\t-h\t\t help: print this help page.\n");
    exit(EXIT_SUCCESS);
}
