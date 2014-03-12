/*
 * File: hash-probing.c
 *
 * Hashmap implementation for the spell-checker
 * using open adressing with linear probing.
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

/*
 * hash_table_new(size)
 * --------------------
 * Initialize a new hashtable with a 2D array for alle elements
 *
 * @param size; elements in the hashtable.
 * @return; an initialized hash hashmap structure with memory allocated
 */
hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = (hash_t*)malloc(sizeof(hash_t));
    table->table = (element_t**)malloc(sizeof(element_t**)*size);
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
    for (unsigned int i = 0; i < table->size; i++) {
        if (!table->table[i]) {
            continue;
        } else {
            free(table->table[i]->key);
            free(table->table[i]);
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

        element_t* element = malloc(sizeof(element_t));
        element->key = key;
        element->value = value;

        /*
         * If the index has no value then place element here,
         * else search for the first open adress to put it in.
         */
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
    unsigned int offset = 0;

    /*
     * While the adress given with the hash function has an element,
     * test if the element is the element being searched.
     */
    while (table->table[(index + offset) % table->size]) {
        if (!strcmp(key, table->table[(index + offset) % table->size]->key))
            return table->table[(index + offset) % table->size];
        offset++;
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
    for (unsigned int i = 0; i < table->size; i++) {
        if (table->table[i]) total_elements++;
    }
    return total_elements;
}
