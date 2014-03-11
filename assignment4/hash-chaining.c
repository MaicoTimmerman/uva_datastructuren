#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

typedef struct linked_node_t linked_node_t;

struct hash_t {
    linked_node_t **table;
    unsigned int size;
};

struct linked_node_t {
    linked_node_t *next;
    char *key;
    char *value;
};

unsigned int hash_function(void* key, unsigned int table_size);

hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = (hash_t*)malloc(sizeof(hash_t));
    table->table = (linked_node_t**)malloc(sizeof(linked_node_t**)*size);
    table->size = size;
    for (unsigned int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

void hash_table_destroy(hash_t* table) {
    linked_node_t* node;
    linked_node_t* next;
    for (unsigned int i = 0; i < table->size; i++) {
        node = table->table[i];
        while (node) {
            next = node->next;
            free(node->value);
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(table->table);
    table->table = NULL;
    free(table);
}

unsigned int hash_function(void* key, unsigned int table_size){

    unsigned int hash = 7;
    unsigned int multiplier = 33;

    char* char_key = (char*)key;

    for (; *char_key; ++char_key)
        hash = multiplier*hash +(int)*char_key;
    return hash % table_size;
}

void hash_table_insert(hash_t* table, char* key, char* value) {
    if (!hash_table_lookup(table, key)) {
        unsigned int index = hash_function(key, table->size);
        linked_node_t* node = malloc(sizeof(linked_node_t*));
        node->key = key;
        node->value = value;
        node->next = NULL;
        if (!table->table[index]) {
            table->table[index] = node;
        } else {
            node->next = table->table[index]->next;
            table->table[index] = node;
        }
    }
}

void* hash_table_lookup(hash_t* table, char* key) {

    unsigned int index = hash_function(key, table->size);
    linked_node_t* node = table->table[index];
    linked_node_t* next;
    if (!node) {
        return NULL;
    } else {
        while (node) {
            if (!strcmp(key, node->key))
                return node;
            next = node->next;
            node = next;
        }
    }
    return NULL;
}

unsigned int hash_table_size(hash_t* table) {
    return table->size;
}

unsigned int hash_table_fill(hash_t* table) {
    unsigned int total_elements = 0;
    linked_node_t* next;
    linked_node_t* node;
    for (unsigned int i = 0; i < table->size; i++) {
        node = table->table[i];
        if (!node) {
            continue;
        } else {
            while (node) {
                total_elements++;
                next = node->next;
                node = next;
            }
        }
    }
    return total_elements;
}
