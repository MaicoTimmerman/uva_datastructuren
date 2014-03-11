#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_node_t linked_node_t;

struct linked_node_t {
    linked_node_t *next;
    char *key;
    char *value;

};

linked_node_t* init_list(char* key, char* value);
linked_node_t* add_node(linked_node_t *previous, char* key, char* value);
void destroy_list(linked_node_t *header);
void* search_element(linked_node_t* header, char* key);
unsigned int size_list(linked_node_t *header);
#endif /* LINKED_LIST_H */
