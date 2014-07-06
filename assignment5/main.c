#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

#include "maze.h"
#include "tree.h"

double print_elapsed_ru(struct rusage start, struct rusage stop);
double get_sec(struct timeval data);

int main (int argc, char** argv) {

    double total_time;
    int steps;
    struct rusage start_tdata, stop_tdata;
    maze_t* maze;
    tree_t* min_span_tree;

    /* check args */
    if (argc != 2) {
        printf("usage: %s <maze file>\n", argv[0]);
        return 2;
    }

    /* Starting timings */
    getrusage(RUSAGE_SELF, &start_tdata);

    /* Read maze */
    maze = read_maze(argv[1]);

    /* Print maze, without marker */
    print_maze(maze, -1, -1);

    /* Create spanning tree, find shortest path and mark it in the
     * maze...*/

    location_t* end = malloc(sizeof(location_t));
    end->row = maze->end_row;
    end->col = maze->end_col;

    min_span_tree = create_spanning_tree(maze);
    print_tree(min_span_tree, "tree.dot");
    steps = mark_shortest_path(min_span_tree, end, maze);

    /* Print maze with shortest path marked. */
    print_maze(maze, -1, -1);

    /* End timings */
    getrusage(RUSAGE_SELF, &stop_tdata);

    total_time = print_elapsed_ru(start_tdata, stop_tdata);
    printf("Average time per square: %lf\n", total_time / (maze->nrows * maze->ncols));
    printf("Length of shortest path: %d\n", steps);
    printf("Oppervlakte of maze: %d\n", (maze->nrows * maze->ncols));

    cleanup_tree(min_span_tree);
    cleanup_maze(maze);
    free(end);

    return EXIT_SUCCESS;
}

/* Helper functions for timing */
double print_elapsed_ru(struct rusage start, struct rusage stop) {
    double tuser, tsystem;
    tuser = get_sec(stop.ru_utime) - get_sec(start.ru_utime);
    tsystem = get_sec(stop.ru_stime) - get_sec(start.ru_stime);
    printf("User cpu time (s):     %f\n", tuser);
    printf("System cpu time (s):   %f\n", tsystem);
    printf("Total cpu time (s):    %f\n", tuser + tsystem);
    return tsystem;
}

double get_sec(struct timeval data) {
    return data.tv_sec + data.tv_usec/1000000.0;
}
