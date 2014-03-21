#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node_t queue_node_t;
struct queue_node_t {
    void* val;
    queue_node_t* prev;
    queue_node_t* next;
};

queue_node_t* new_queue();
int is_empty(queue_node_t* q);
void enqueue(queue_node_t* q, void* element);
void* dequeue(queue_node_t* q);
void cleanup_queue(queue_node_t* queue);

#endif /* QUEUE_H */
