//
// Created by Ignorant on 2025/5/6.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <pthread.h>

typedef struct node_t {
    int key;
    struct node_t *next;
} node_t;

typedef struct list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void list_init(list_t *list);

int list_insert(list_t *list, int key);

int list_search(list_t *list, int key);

int list_remove(list_t *list, int key);

void list_delete(list_t *list);

#endif //LINKED_LIST_H
