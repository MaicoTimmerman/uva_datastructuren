typedef struct hash_t hash_t;

hash_t* hash_table_new(unsigned int size);
void hash_table_destroy(hash_t* table);
void hash_table_insert(hash_t* table, char* key, char* value);
void* hash_table_lookup(hash_t* table, char* key);
unsigned int hash_table_size(hash_t* table);
unsigned int hash_table_fill(hash_t* table);
