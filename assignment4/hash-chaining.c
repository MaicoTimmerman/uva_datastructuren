#include <stdlib.h>
#include <glib.h>

#include "hash.h"
#include "linked-list.c"

struct hash_t {
    linked_header_t *table;
};

hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    return NULL;
}

void hash_table_destroy(hash_t* table) {
}

void hash_table_insert(hash_t* table, void* key, void* value) {
}

void* hash_table_lookup(hash_t* table, void* key) {
}

unsigned int hash_table_size(hash_t* table) {
}

unsigned int hash_table_fill(hash_t* table) {
}
