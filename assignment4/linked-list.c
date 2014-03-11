#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked-list.h"

linked_node_t* init_list(char* key, char* value) {
    linked_node_t* node = malloc(sizeof(linked_node_t));
    if (node) {
        node->value = value;
        node->next = NULL;
        node->key = key;
        return node;
    }
    return NULL;
}

linked_node_t* add_node(linked_node_t* previous, char* key, char* value) {
    linked_node_t *node = malloc(sizeof(linked_node_t));
    if (node) {
        node->next = previous;
        node->value = value;
        node->key = key;
    }
    return node;
}

void destroy_list(linked_node_t *node) {
    linked_node_t *next;
    if (!node)
        return;
    while (node) {
        next = node->next;
        free(node->value);
        free(node->key);
        free(node);
        node = next;
    }
}

void* search_element(linked_node_t* node, char* key) {
    if (!node)
        return NULL;
    linked_node_t *next;
    while (node) {
        if (strcmp(node->key, key)) {
            return node;
        }
        next = node->next;
        node = next;
    }
    return NULL;
}

unsigned int size_list(linked_node_t *node) {
    if (!node)
        return 0;
    linked_node_t *next;
    unsigned int size = 0;
    while (node) {
        next = node->next;
        node = next;
        size++;
    }
    return size;
}
