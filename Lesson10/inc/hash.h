//
// Created by Ignorant on 2025/5/6.
//

#ifndef HASH_H
#define HASH_H

#include "linked_list.h"

#define BUCKETS (101)

typedef struct hash_t {
    list_t lists[BUCKETS];
} hash_t;

void hash_init(hash_t *hash);

int hash_insert(hash_t *hash, int key);

int hash_search(hash_t *hash, int key);

#endif //HASH_H
