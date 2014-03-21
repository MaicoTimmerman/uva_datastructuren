#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "queue.h"
#include "maze.h"

#define MARKING '@'

/*
 * Function: create_spanning_tree()
 * -------------------
 * Creates a tree based on the maze, the paths are based on the
 * shortest route to the root of the tree.
 * Every node of the tree has variable amount of children,
 * depending on how many walls there are next to it.
 *
 * @param maze_t* maze; Pointer to the maze structure.
 * @returns; pointer to the root of the tree structure.
 */
tree_t* create_spanning_tree(maze_t *maze) {

    /* Initialize the queue */
    queue_node_t* queue = new_queue();

    /* Initialize root of the tree */
    tree_t* root = new_tree_node(NULL, maze->start_row, maze->start_col);
    enqueue(queue, root);

    int row, col;
    tree_t* new_node;
    tree_t* node;

    /*
     * While the queue is not empty take the first item
     * in the queue and get all not used neightbours.
     */
    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue))) {
            break;
        }
        row = node->location->row;
        col = node->location->col;

        /*
         * Find all 4 sides, enqueue them, add them to the tree
         * Mark them temporary as used so the following node wont take it as nearest.
         */
        switch (maze->map[row+1][col]) {
            case WALL:
            case START:
            case MARKING:
                break;
            case EXIT:
            case OPEN:
                maze->map[row+1][col] = MARKING;
                new_node = new_tree_node(node, row+1, col);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row-1][col]) {
            case WALL:
            case START:
            case MARKING:
                break;
            case EXIT:
            case OPEN:
                maze->map[row-1][col] = MARKING;
                new_node = new_tree_node(node, row-1, col);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row][col+1]) {
            case WALL:
            case START:
            case MARKING:
                break;
            case EXIT:
            case OPEN:
                maze->map[row][col+1] = MARKING;
                new_node = new_tree_node(node, row, col+1);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row][col-1]) {
            case WALL:
            case START:
            case MARKING:
                break;
            case EXIT:
            case OPEN:
                maze->map[row][col-1] = MARKING;
                new_node = new_tree_node(node, row, col-1);
                enqueue(queue, new_node);
                break;
            default:
                break;
        }

    }
    /* Remove all the markings */
    for (int i = 0; i < maze->nrows; i++) {
        for (int j = 0; j < maze->ncols; j++) {
            if (maze->map[i][j] == MARKING)
                maze->map[i][j] = OPEN;
        }
    }

    /* Set the exit back */
    maze->map[maze->end_row][maze->end_col] = EXIT;
    free(queue);
    return root;
}

/*
 * Function: print_tree()
 * -------------------
 * Create a file with the formatting to create a Graphviz tree graph.
 *
 * @param tree_t* root; Pointer to the root of the tree structure.
 * @param char* filename; A filename to print the graph to.
 * @returns; void.
 */
void print_tree(tree_t* root, char* filename) {

    FILE* fp;
    queue_node_t* queue;
    tree_t* node;

    fp = fopen(filename, "w");

    /* Add root to the queue */
    queue = new_queue();
    enqueue(queue, root);

    fprintf(fp, "digraph BST{\n");
    fprintf(fp, "node [fontname=\"Arial\"]\n");

    /* For every node in the queue print the vertex to its children */
    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue)))
            break;
        /* For all children of the node */
        for (int i = 0; i < node->n_children; i++) {
            enqueue(queue, node->children[i]);
            fprintf(fp, "\t\"%d,%d\" -> \"%d,%d\"\n",
                    node->location->row,
                    node->location->col,
                    node->children[i]->location->row,
                    node->children[i]->location->col
                    );
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
    free(queue);
}

/*
 * Function: new_tree_node()
 * -------------------------
 * Create a new tree node with the given parent and location.
 *
 * @param tree_t* parent; Pointer to the parent of the new tree structure.
 * @param int row; The row of the new node.
 * @param int col; The col of the new node.
 * @returns tree_t*; Pointer to the new initialized structure.
 */
tree_t* new_tree_node(tree_t* parent, int row, int col) {

    /* Create a new node and set its data. */
    tree_t* tree = malloc(sizeof(tree_t));
    assert(tree);
    tree->location = malloc(sizeof(location_t));
    assert(tree->location);
    tree->location->row = row;
    tree->location->col = col;
    tree->parent = parent;
    tree->children = NULL;
    tree->n_children = 0;

    /* If a parent was given(no root node), then add it to the parent as child */
    if (parent) {
        tree_t** temp_ptr = realloc(parent->children, sizeof(tree_t*) * ++(parent->n_children));
        assert(temp_ptr);
        parent->children = temp_ptr;
        parent->children[(parent->n_children) - 1] = tree;
    }
    return tree;
}

/*
 * Function: mark_shortest_path()
 * -------------------------
 * Mark the shortest path in the maze with dots.
 *
 * @param tree_t* root; Pointer to the root of the new tree structure.
 * @param location_t* exit; location of the exit to search for in the tree.
 * @param maze_t* maze; Pointer to the maze structure to mark the shortest path in
 * @returns tree_t*; Pointer to the new initialized structure.
 */
int mark_shortest_path(tree_t* root, location_t* exit, maze_t* maze) {

    queue_node_t* queue;
    tree_t* node;

    /* Add the root to the queue */
    queue = new_queue();
    enqueue(queue, root);

    /* For every node in the queue add all its children to the queue */
    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue)))
            break;
        /*
         * if the node is the exit node, the bubble through its parents
         * and mark every square in the maze with a dot
         */
        if (node->location->row == exit->row && node->location->col == exit->col) {
            while (node) {
                maze->map[node->location->row][node->location->col] = PATH;
                node = node->parent;
            }
            /* Replace EXIT and START in the maze, because they have been overwritten. */
            maze->map[maze->end_row][maze->end_col] = EXIT;
            maze->map[maze->start_row][maze->start_col] = START;

            /* Remove all remaining elements in the queue */
            while (!is_empty(queue)) {
                dequeue(queue);
            }
            free(queue);
            return 1;
        }
        /* The node was not the current node, so add all his children. */
        for (int i = 0; i < node->n_children; i++) {
            enqueue(queue, node->children[i]);
        }
    }
    free(queue);
    return 0;
}

/*
 * Function: cleanup_tree()
 * -------------------------
 * Free all memory used by the tree structure.
 *
 * @param tree_t* root; Pointer to the root of the new tree structure.
 * @returns; void.
 */
void cleanup_tree(tree_t *root) {
    queue_node_t* queue;
    tree_t* node;

    /* Add the root tot the queue */
    queue = new_queue();
    enqueue(queue, root);

    /* While the queue is not empty, enqueue all children and free the current node. */
    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue)))
            break;
        for (int i = 0; i < node->n_children; i++) {
            enqueue(queue, node->children[i]);
        }
        free(node->location);
        free(node->children);
        free(node);
    }
    free(queue);
    return;
}
