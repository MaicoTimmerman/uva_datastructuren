#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "queue.h"
#include "maze.h"

tree_t* create_spanning_tree(maze_t *maze) {

    /* Initialize the queue */
    queue_node_t* queue = new_queue();

    /* Initialize root of the tree */
    tree_t* root = new_tree_node(NULL, maze->start_row, maze->start_col);
    enqueue(queue, root);

    int row, col;
    tree_t *new_node;
    tree_t *node;

    /* While the queue is not empty take the first item in the queue and get all not used neightbours. */
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
            case '@':
                break;
            case EXIT:
            case OPEN:
                maze->map[row+1][col] = '@';
                new_node = new_tree_node(node, row+1, col);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row-1][col]) {
            case WALL:
            case START:
            case '@':
                break;
            case EXIT:
            case OPEN:
                maze->map[row-1][col] = '@';
                new_node = new_tree_node(node, row-1, col);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row][col+1]) {
            case WALL:
            case START:
            case '@':
                break;
            case EXIT:
            case OPEN:
                maze->map[row][col+1] = '@';
                new_node = new_tree_node(node, row, col+1);
                enqueue(queue, new_node);
            default:
                break;
        }
        switch (maze->map[row][col-1]) {
            case WALL:
            case START:
            case '@':
                break;
            case EXIT:
            case OPEN:
                maze->map[row][col-1] = '@';
                new_node = new_tree_node(node, row, col-1);
                enqueue(queue, new_node);
                break;
            default:
                break;
        }

    }
    /* Remove all the markers */
    for (int i = 0; i < maze->nrows; i++) {
        for (int j = 0; j < maze->ncols; j++) {
            if (maze->map[i][j] == '@')
                maze->map[i][j] = OPEN;
        }
    }

    /* Set the exit back */
    maze->map[maze->end_row][maze->end_col] = EXIT;
    cleanup_queue(queue);
    return root;
}

void print_tree(tree_t *root, char *filename) {

    FILE *fp;
    queue_node_t* queue;
    tree_t *node;

    fp = fopen(filename, "w");

    queue = new_queue();
    enqueue(queue, root);

    fprintf(fp, "digraph BST{\n");
    fprintf(fp, "node [fontname=\"Arial\"]\n");

    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue)))
            break;
        for (int i = 0; i < node->n_children; i++) {
            enqueue(queue, node->children[i]);
            fprintf(fp, "\t\"%d,%d\" -> \"%d,%d\"\n",
                    node->location->col,
                    node->location->row,
                    node->children[i]->location->col,
                    node->children[i]->location->row);
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
    cleanup_queue(queue);
}

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

/* Implement a search algorithm throught the tree */
int mark_shortest_path(tree_t *root, location_t *exit, maze_t *maze) {

    queue_node_t* queue;
    tree_t *node;

    queue = new_queue();
    enqueue(queue, root);

    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue)))
            break;
        if (node->location->row == exit->row && node->location->col == exit->col) {
            while (node) {
                maze->map[node->location->row][node->location->col] = PATH;
                node = node->parent;
            }
            maze->map[maze->end_row][maze->end_col] = EXIT;
            maze->map[maze->start_row][maze->start_col] = START;
            cleanup_queue(queue);
            return 1;
        }
        for (int i = 0; i < node->n_children; i++) {
            enqueue(queue, node->children[i]);
        }
    }
    cleanup_queue(queue);
    return 0;
}

void cleanup_tree(tree_t *root) {
    queue_node_t* queue;
    tree_t *node;

    queue = new_queue();
    enqueue(queue, root);

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
    cleanup_queue(queue);
    return;
}

