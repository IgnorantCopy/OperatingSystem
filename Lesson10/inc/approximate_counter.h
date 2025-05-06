//
// Created by Ignorant on 2025/5/6.

#ifndef APPROXIMATE_COUNTER_H
#define APPROXIMATE_COUNTER_H

#include <pthread.h>
#include <unistd.h>

#define CPUS (sysconf(_SC_NPROCESSORS_ONLN))

typedef struct approximate_counter_t {
    int global_count;
    pthread_mutex_t glock;
    int local_count[CPUS];
    pthread_mutex_t llock[CPUS];
    int threshold;
} approximate_counter_t;

void approximate_counter_init(approximate_counter_t *counter, int threshold);

void approximate_counter_update(approximate_counter_t *counter, int threadId, int amount);

int approximate_counter_get(approximate_counter_t *counter);

#endif //APPROXIMATE_COUNTER_H
