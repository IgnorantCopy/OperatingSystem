//
// Created by Ignorant on 2025/5/6.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct node_t {
    int value;
    struct node_t* next;
} node_t;

typedef struct queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t headLock;
    pthread_mutex_t tailLock;
} queue_t;

void queue_init(queue_t* queue);

void queue_enqueue(queue_t* queue, int value);

int queue_dequeue(queue_t* queue, int *value);

#endif //QUEUE_H
