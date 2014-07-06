#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/*
 * Function: new_queue()
 * -------------------
 * Allocates memory for an empty queue.
 *
 * @returns; An empty queue.
 */
queue_node_t* new_queue() {
    queue_node_t* q = malloc(sizeof(queue_node_t));
    q->next = q->prev = NULL;
    return q;
}

/*
 * Function: is_empty()
 * -------------------
 * Tests if the queue is empty.
 *
 * @returns; boolean value for empty.
 */
int is_empty(queue_node_t* q) {
    return !q->prev;
}

/*
 * Function: enqueue()
 * -------------------
 * Enqueues a new value to the queue.
 *
 * @param queue_node_t* q; Pointer to the queue to add value to.
 * @param void* val; Pointer to the value to add to the queue.
 * @returns; void.
 */
void enqueue(queue_node_t* q, void* val) {

    queue_node_t* new_node = malloc(sizeof(queue_node_t));
    assert(new_node);
    new_node->val = val;

    if (!q->prev)
        q->prev = new_node;

    new_node->prev = q->next;

    if (new_node->prev)
        new_node->prev->next = new_node;

    q->next = new_node;
    new_node->next = NULL;
}

/*
 * Function: dequeue()
 * -------------------
 * Dequeues the next value from the queue.
 *
 * @param queue_node_t* q; Pointer to the queue where to dequeue from.
 * @returns void*; Pointer to the value returned.
 */
void* dequeue(queue_node_t* q) {
    void* val;

    queue_node_t* temp = q->prev;
    /* Queue is empty */
    if (!temp)
        return NULL;

    val = temp->val;
    assert(val);

    /* Set the next element ready in the queue. */
    q->prev = temp->next;
    if (q->next == temp)
        q->next = NULL;

    free(temp);

    return val;
}
