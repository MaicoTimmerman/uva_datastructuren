#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

queue_node_t* new_queue() {
    queue_node_t* q = malloc(sizeof(queue_node_t));
    q->next = q->prev = NULL;
    return q;
}

int is_empty(queue_node_t* q) {
    return !q->prev;
}

void enqueue(queue_node_t* q, void* val) {
    queue_node_t* new_node = malloc(sizeof(queue_node_t));
    new_node->val = val;

    if (!q->prev)
        q->prev = new_node;

    new_node->prev = q->next;
    if (new_node->prev)
        new_node->prev->next = new_node;

    q->next = new_node;
    new_node->next = NULL;
}

void* dequeue(queue_node_t* q) {
    void* val;

    queue_node_t* temp = q->prev;
    if (!temp)
        return NULL;

    val = temp->val;
    assert(val);

    q->prev = temp->next;
    if (q->next == temp)
        q->next = NULL;
    free(temp);

    return val;
}

void cleanup_queue(queue_node_t* queue) {
    void* val;
    while (!is_empty(queue)) {
        val = dequeue(queue);
        free(val);
    }
    free(queue);
}
