#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_header_t linked_header_t;
typedef struct linked_node_t linked_node_t;

struct linked_node_t {
    linked_node_t *next;
    char *key;
    char *value;

};

struct linked_header_t {
    linked_node_t *first;
    unsigned int size;
};

linked_header_t* init_list();
void add_node(linked_header_t *header,char* key, char* value);
void destroy_list(linked_header_t *header);
void* search_element(linked_header_t* header, char* key);
unsigned int size_list(linked_header_t *header);
#endif /* LINKED_LIST_H */
