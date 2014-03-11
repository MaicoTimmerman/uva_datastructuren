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


void add_node(linked_header_t *header,char* key, char* value) {
    linked_node_t *node = malloc(sizeof(linked_node_t));
    if (node) {
        node->next = header->first;
        node->value = value;
        node->key = key;
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
        free(node->value);
        free(node);
        node = next;
    }
    free(header);
}

void* search_element(linked_header_t* header, char* key) {
    linked_node_t *node;
    linked_node_t *next;
    node = header->first;
    while (node) {
        if (*(node->key) == *key) {
            return node;
        }
        next = node->next;
        node = next;
    }
    return NULL;
}

unsigned int size_list(linked_header_t *header) {
    return header->size;
}
