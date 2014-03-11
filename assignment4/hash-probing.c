#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

typedef struct element_t element_t;

struct element_t {
    char *key;
    char *value;
};

struct hash_t {
    element_t **table;
    unsigned int size;
};

unsigned int hash_function(void* key, unsigned int table_size);

hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = (hash_t*)malloc(sizeof(hash_t));
    table->table = (element_t**)malloc(sizeof(element_t**)*size);
    table->size = size;
    for (unsigned int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

void hash_table_destroy(hash_t* table) {
    for (unsigned int i = 0; i < table->size; i++) {
        if (!table->table[i])
            continue;
        free(table->table[i]->key);
        free(table->table[i]->value);
        free(table->table[i]);

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
        element_t* element = malloc(sizeof(element_t*));
        element->key = key;
        element->value = value;
        if (!table->table[index]) {
            table->table[index] = element;
        } else {
            unsigned int offset = 0;
            while (table->table[(index + offset) % table->size]) {
                offset++;
            }
            table->table[(index + offset) % table->size] = element;
        }
    }
}

void* hash_table_lookup(hash_t* table, char* key) {

    unsigned int index = hash_function(key, table->size);
    unsigned int offset = 0;
    while (table->table[(index + offset) % table->size]) {
        if (!strcmp(key, table->table[(index + offset) % table->size]->key))
            return table->table[(index + offset) % table->size];
        offset++;
    }
    return NULL;
}

unsigned int hash_table_size(hash_t* table) {
    return table->size;
}

unsigned int hash_table_fill(hash_t* table) {
    unsigned int total_elements = 0;
    for (unsigned int i = 0; i < table->size; i++) {
        if (table->table[i]) total_elements++;
    }
    return total_elements;
}
