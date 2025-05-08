//
// Created by Ignorant on 2025/5/6.
//

#include "hash.h"


void hash_init(hash_t *hash) {
    for (int i = 0; i < BUCKETS; i++) {
        list_init(&hash->lists[i]);
    }
}

int hash_insert(hash_t *hash, const int key) {
    const int bucket = key % BUCKETS;
    return list_insert(&hash->lists[bucket], key);
}

int hash_search(hash_t *hash, const int key) {
    const int bucket = key % BUCKETS;
    return list_search(&hash->lists[bucket], key);
}

int main() {
    
    return 0;
}
