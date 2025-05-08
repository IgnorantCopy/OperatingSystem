//
// Created by Ignorant on 2025/5/6.
//

#ifndef PRECISE_COUNTER_H
#define PRECISE_COUNTER_H

#include <pthread.h>

typedef struct precise_counter_t {
    int value;
    pthread_mutex_t lock;
} precise_counter_t;

void precise_counter_init(precise_counter_t *counter);

void precise_counter_increment(precise_counter_t *counter);

void precise_counter_decrement(precise_counter_t *counter);

int precise_counter_get(precise_counter_t *counter);

#endif //PRECISE_COUNTER_H
