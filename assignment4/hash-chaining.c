/*
 * File: hash-chaining.c
 *
 * Hashmap implementation for the spell-checker using collision chaining.
 *
 * @author: Maico Timmerman
 * @uvanetid: 10542590
 * @date: 12 march 2014
 * @version: 1.0
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

typedef struct linked_node_t linked_node_t;

struct linked_node_t {
    linked_node_t *next;
    char *key;
    char *value;
};

struct hash_t {
    linked_node_t **table;
    unsigned int size;
};


unsigned int hash_function(void* key, unsigned int table_size);

/*
 * hash_table_new(size)
 * --------------------
 * Initialize a new hashtable with a 2D array for alle elements
 *
 * @param size; elements in the hashtable.
 * @return; an initialized hash hashmap structure with memory allocated
 */
hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = malloc(sizeof(hash_t));
    table->table = malloc(sizeof(linked_node_t*)*size);
    table->size = size;
    for (unsigned int i = 0; i < size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

/*
 * hash_table_destroy(size)
 * ------------------------
 * Clean up the whole structure and release all memory.
 *
 * @param hash_t *table; a pointer to an initialized hashtable.
 * @return; void.
 */
void hash_table_destroy(hash_t* table) {
    linked_node_t* node;
    linked_node_t* next;
    for (unsigned int i = 0; i < table->size; i++) {
        node = table->table[i];
        /* Destroy the whole linked list */
        while (node) {
            next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(table->table);
    table->table = NULL;
    free(table);
}

/*
 * hash_function(key, table_size)
 * ------------------------------
 * Calculate an index with the given key. Limits the index to the maximum table size.
 *
 * @param *key; a pointer to the key used to calculate the hash.
 * @param table_size; the size of the table.
 * @return; the calculated index.
 */
unsigned int hash_function(void* key, unsigned int table_size){

    unsigned int hash = 7;
    unsigned int multiplier = 33;

    char* char_key = (char*)key;

    for (; *char_key; ++char_key)
        hash = multiplier*hash +(int)*char_key;
    return hash % table_size;
}

/*
 * hash_table_insert(table, key, value)
 * ------------------------------------
 * Insert the given key and value pair in the hashtable if it doesnt exist already.
 *
 * @param *table; a pointer the the hashtable that the element should be inserted in.
 * @param *key; a pointer to the key.
 * @param *value; a pointer to the value.
 * @return; void.
 */
void hash_table_insert(hash_t* table, char* key, char* value) {

    if (!hash_table_lookup(table, key)) {
        unsigned int index = hash_function(key, table->size);

        linked_node_t* node = malloc(sizeof(linked_node_t));
        node->key = key;
        node->value = value;
        node->next = NULL;

        /*
         * If the index has no value, then place it
         * else put the currect node behind the new one
         */
        if (!table->table[index]) {
            table->table[index] = node;
        } else {
            node->next = table->table[index];
            table->table[index] = node;
        }
    }
}

/*
 * hash_table_lookup(table, key)
 * -----------------------------
 * Test if an item with the given key already exists in the hashtable.
 * Returns NULL if not found and the element if found.
 *
 * @param *table; a pointer the the hashtable that the element should be inserted in.
 * @param *key; a pointer to the key.
 * @return; NULL/element.
 */
void* hash_table_lookup(hash_t* table, char* key) {

    unsigned int index = hash_function(key, table->size);
    linked_node_t* node = table->table[index];
    linked_node_t* next;

    /* Iterate over every item in the linked list */
    while (node) {
        if (!strcmp(key, node->key))
            return node;
        next = node->next;
        node = next;
    }
    return NULL;
}

/*
 * hash_table_size(table)
 * ----------------------
 * Returns the size of the table.
 *
 * @param *table; a pointer the the hashtable that the element should be inserted in.
 * @param *key; a pointer to the key.
 * @return; NULL/element.
 */
unsigned int hash_table_size(hash_t* table) {
    return table->size;
}

/*
 * hash_table_fill(table)
 * ----------------------
 * Returns the amount of elements in the hashtable.
 *
 * @param *table; a pointer the the hashtable that the element should be inserted in.
 * @return; number of elements.
 */
unsigned int hash_table_fill(hash_t* table) {
    unsigned int total_elements = 0;
    linked_node_t* next;
    linked_node_t* node;
    for (unsigned int i = 0; i < table->size; i++) {
        node = table->table[i];
        /* For every node in the list increase total */
        while (node) {
            total_elements++;
            next = node->next;
            node = next;
        }
    }
    return total_elements;
}
