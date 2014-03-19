#ifndef TREE_H
#define TREE_H

#include "maze.h"

/* row,col pair used by a tree node to store its location in the maze. */
typedef struct {
    int row;
    int col;
} location_t;

typedef struct tree_t tree_t;

struct tree_t {
    location_t* location;
    tree_t* parent;
    tree_t** children;
    int n_children;
};

tree_t* create_spanning_tree(maze_t *maze);
void print_tree(tree_t *root, char *filename);
tree_t* new_tree_node(tree_t* parent, int row, int col);
int mark_shortest_path(tree_t *node, location_t *exit, maze_t *maze);
void cleanup_tree(tree_t *node);
#endif /* TREE_H */
