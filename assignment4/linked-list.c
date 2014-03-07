#include <stdlib.h>
#include <stdio.h>

#include "linked-list.h"

linked_header_t* init_list() {
    linked_header_t *header = malloc(sizeof(linked_header_t));
    if (header) {
        header->first = NULL;
        header->size = 0;
        return header;
    }
    return NULL;
}


void add_node(linked_header_t *header, void *value) {
    linked_node_t *node = malloc(sizeof(linked_node_t));
    if (node) {
        node->next = header->first;
        node->element = value;
        header->first = node;
        header->size += 1;
    }
}

void destroy_list(linked_header_t *header) {
    linked_node_t *node;
    linked_node_t *next;
    node = header->first;
    while (node) {
        next = node->next;
        free(node->element);
        free(node);
        node = next;
    }
    free(header);
}

unsigned int size_elements_list(linked_header_t *header) {
    return header->size;
}
unsigned int size_raw_list(linked_header_t *header){
    int total_bytes;
    linked_node_t *node;
    linked_node_t *next;
    node = header->first;
    while (node) {
        next = node->next;
        total_bytes += sizeof(*(node->element));
        total_bytes += sizeof(node);
        node = next;
    }
}
