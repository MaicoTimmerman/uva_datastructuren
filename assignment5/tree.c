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
    fprintf(stderr, "**maze->map[%d][%d]: %c;\n",maze->start_row, maze->start_col, maze->map[maze->start_row][maze->start_col]);

    int row, col;
    tree_t *node = NULL;
    tree_t *new_node;

    /* For every node in the queue get all neightbours and add them to the tree and queue. */
    // FIXME: Adding nodes and fix realloc crash
    while (!is_empty(queue)) {
        if (!(node = (struct tree_t*)dequeue(queue))) {
            break;
            fprintf(stderr, "BREAK\n");
        }
        fprintf(stderr, "node: %p\n", (void*)node);
        fprintf(stderr, "node->location: %p\n", (void*)node->location);
        row = node->location->row;
        col = node->location->col;


        /* Find all 4 sides, enqueue them, add them to the tree and mark them temporary. */
        switch (maze->map[row+1][col]) {
            case WALL:
            case START:
            case '@':
                break;
            case EXIT:
            case OPEN:
                fprintf(stderr, "maze->map[%d][%d]: %c;\n",row+1, col, maze->map[row+1][col]);
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
                fprintf(stderr, "maze->map[%d][%d]: %c;\n",row-1, col, maze->map[row-1][col]);
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
                fprintf(stderr, "maze->map[%d][%d]: %c;\n",row, col+1, maze->map[row][col+1]);
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
                fprintf(stderr, "maze->map[%d][%d]: %c;\n",row, col-1, maze->map[row][col-1]);
                maze->map[row][col-1] = '@';
                new_node = new_tree_node(node, row, col-1);
                enqueue(queue, new_node);
                break;
            default:
                break;
        }

    }
    for (int i = 0; i < maze->nrows; i++) {
        for (int j = 0; j < maze->ncols; j++) {
            if (maze->map[i][j] == '@')
                maze->map[i][j] = OPEN;
        }
    }
    maze->map[maze->end_row][maze->end_col] = EXIT;
    return root;
}

void print_tree(tree_t *root, char *filename) {
    FILE *fp;
    queue_node_t* queue;
    tree_t *node = NULL;

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
            if (node->parent) {
                fprintf(fp, "\t\"%d,%d\" -> \"%d,%d\"\n",
                        node->parent->location->col,
                        node->parent->location->row,
                        node->location->col,
                        node->location->row);
            }
        }
    }
    fprintf(fp, "}\n");

    char* unixcommand = strcat("dot -Tpng ", strcat(filename,  strcat(" > ", strcat(filename, ".png"))));
    fprintf(stdout, "%s", unixcommand);
    system(unixcommand);

    fclose(fp);

}

tree_t* new_tree_node(tree_t* parent, int row, int col) {
    tree_t* tree = malloc(sizeof(tree_t));
    tree->location = malloc(sizeof(location_t));
    tree->location->row = row;
    tree->location->col = col;
    tree->parent = parent;
    tree->n_children = 0;

    fprintf(stderr, "Creating new node, (%d,%d) at %p\n", row, col, (void*)tree);
    fprintf(stderr, "parent: %p\n", (void*)parent);


    if (parent) {
        fprintf(stderr, "parent->children test: %p\n", (void*)parent->children);
        if (parent->children) {
            tree_t** temp_ptr = realloc(parent->children, sizeof(tree_t*) * ++(parent->n_children));
            assert(temp_ptr);
            parent->children = temp_ptr;
            fprintf(stderr, "parent->children realloc'd: %p\n", (void*)parent->children);
            fprintf(stderr, "realloc succes!\n");
        } else {
            parent->children = malloc(sizeof(tree_t*) * ++(parent->n_children));
            fprintf(stderr, "parent->children malloc'd: %p\n", (void*)parent->children);
        }
        parent->children[(parent->n_children) - 1] = tree;
    }
    fprintf(stderr, "\n");
    return tree;
}

/* Implement a search algorithm throught the tree */
/* int mark_shortest_path(tree_t *node, location_t *exit, maze_t *maze) { */
/*     return 1; */
/* } */
/*  */
/* void cleanup_tree(tree_t *node) { */
/*     return; */
/* } */

