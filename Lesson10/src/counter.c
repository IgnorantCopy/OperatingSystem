//
// Created by Ignorant on 2025/5/6.
//

#include "precise_counter.h"
#include "approximate_counter.h"

/**
 * precise counter
 */
void precise_counter_init(precise_counter_t *counter) {
    counter->value = 0;
    pthread_mutex_init(&counter->lock, nullptr);
}

void precise_counter_increment(precise_counter_t *counter) {
    pthread_mutex_lock(&counter->lock);
    counter->value++;
    pthread_mutex_unlock(&counter->lock);
}

void precise_counter_decrement(precise_counter_t *counter) {
    pthread_mutex_lock(&counter->lock);
    counter->value--;
    pthread_mutex_unlock(&counter->lock);
}

int precise_counter_get(precise_counter_t *counter) {
    pthread_mutex_lock(&counter->lock);
    const int ret = counter->value;
    pthread_mutex_unlock(&counter->lock);
    return ret;
}

/**
 * approximate counter
 */
void approximate_counter_init(approximate_counter_t *counter, int threshold) {
    counter->threshold = threshold;
    counter->global_count = 0;
    pthread_mutex_init(&counter->glock, nullptr);
    for (int i = 0; i < CPUS; i++) {
        counter->local_count[i] = 0;
        pthread_mutex_init(&counter->llock[i], nullptr);
    }
}

void approximate_counter_update(approximate_counter_t *counter, const int threadId, const int amount) {
    pthread_mutex_lock(&counter->llock[threadId]);
    counter->local_count[threadId] += amount;
    if (counter->local_count[threadId] > counter->threshold) {
        pthread_mutex_lock(&counter->glock);
        counter->global_count += counter->local_count[threadId];
        pthread_mutex_unlock(&counter->glock);
        counter->local_count[threadId] = 0;
    }
    pthread_mutex_unlock(&counter->llock[threadId]);
}

int approximate_counter_get(approximate_counter_t *counter) {
    pthread_mutex_lock(&counter->glock);
    const int ret = counter->global_count;
    pthread_mutex_unlock(&counter->glock);
    return ret;
}

int main() {
    
    return 0;
}
