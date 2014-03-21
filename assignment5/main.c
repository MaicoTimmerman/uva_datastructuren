#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "tree.h"

int main (int argc, char **argv) {
    maze_t *maze;
    tree_t *min_span_tree;

    /* check args */
    if (argc != 2) {
        printf("usage: %s <maze file>\n", argv[0]);
        return 2;
    }

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
    mark_shortest_path(min_span_tree, end, maze);

    /* Print maze with shortest path marked. */
    print_maze(maze, -1, -1);

    cleanup_tree(min_span_tree);
    cleanup_maze(maze);
    free(end);
    return 0;
}
