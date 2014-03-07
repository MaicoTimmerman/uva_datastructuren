#include <stdlib.h>
#include <glib.h>
#include "hash.h"

// FIXME: 5k of reachable memory left.
//
/* hash_t is just a wrapper for GHashTable. */
struct hash_t {
    GHashTable *table;
};

/* We cannot set the size in a glib hash table. So we ignore the
 * size parameter here. */
hash_t* hash_table_new(unsigned int size __attribute__((unused)) ) {
    hash_t *table = malloc(sizeof(hash_t));
    /* Use str_hash as hash function, and g_str_equal to compare the
     * keys. Use free function to free the keys, but don't free the
     * value placeholder. */
    table->table = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    return table;
}

void hash_table_destroy(hash_t* table) {
    g_hash_table_destroy(table->table);
    free(table);
}

void hash_table_insert(hash_t* table, void* key, void* value) {
    /* Will actually replace our token 'a' character. That's ok. */
    g_hash_table_insert(table->table, key, value);
}

void* hash_table_lookup(hash_t* table, void* key) {
    return g_hash_table_lookup(table->table, key);
}

/* glib does not allow us to access the actual size of the hash table.
 * So just return the fill size here as well. */
unsigned int hash_table_size(hash_t* table) {
    return g_hash_table_size(table->table);
}

unsigned int hash_table_fill(hash_t* table) {
    return g_hash_table_size(table->table);
}
