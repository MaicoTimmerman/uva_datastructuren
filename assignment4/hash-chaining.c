#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "linked-list.h"

struct hash_t {
    linked_header_t **table;
    unsigned int size;
};

unsigned int hash_function(void* key, unsigned int table_size);

hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = (hash_t*)malloc(sizeof(hash_t));
    table->table = (linked_header_t**)malloc(sizeof(linked_header_t**) * size);
    table->size = size;
    for (unsigned int i = 0; i < size; i++) {
        table->table[i] = malloc(sizeof(linked_header_t*) * size);
        table->table[i] = NULL;
    }
    return table;
}

void hash_table_destroy(hash_t* table) {
    for (unsigned int i = 0; i < table->size; i++) {
        destroy_list(table->table[i]);
        table->table[i] = NULL;
    }
    free(table->table);
    table->table = NULL;

    free(table);
    table = NULL;
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
        if (!table->table[index]) {
            table->table[index] = init_list();
            add_node(table->table[index], key, value);
        } else {
            add_node(table->table[index], key, value);
        }
    }
}

void* hash_table_lookup(hash_t* table, char* key) {
    unsigned int index = hash_function(key, table->size);
    void* element = search_element(table->table[index], key);
    if (element) {
        return element;
    }
    return NULL;
}

unsigned int hash_table_size(hash_t* table) {
    return table->size;
}

unsigned int hash_table_fill(hash_t* table) {
    int total_elements = 0;
    for (unsigned int i = 0; i < table->size; i++) {
        total_elements += size_list(table->table[i]);
    }
    return total_elements;
}
