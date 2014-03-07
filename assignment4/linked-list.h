#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_header_t linked_header_t;
typedef struct linked_node_t linked_node_t;

struct linked_node_t {
    linked_node_t *next;
    void *element;
};

struct linked_header_t {
    linked_node_t *first;
    unsigned int size;
};

linked_header_t* init_list();
void add_node(linked_header_t *header, void *value);
void destroy_list(linked_header_t *header);
unsigned int size_elements_list(linked_header_t *header);
unsigned int size_raw_list(linked_header_t *header);
#endif /* LINKED_LIST_H */
