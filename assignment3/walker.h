#ifndef WALKER_H
#define WALKER_H

/* Incomplete type declaration. */
typedef struct {
    int col;
    int row;
    int last_move;
} walker_t;


walker_t* init_walker(int verbose, maze_t* maze );
int at_exit(int verbose, maze_t* maze, walker_t* walker);
int check_move(int verbose, maze_t* maze, walker_t* walker, int direction);
int move_walker(int verbose, maze_t* maze, walker_t* walker, int direction);
void cleanup_walker(walker_t* walker);

#endif /* WALKER_H */
