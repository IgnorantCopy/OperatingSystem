//
// Created by root on 5/20/25.
//


#include <pthread.h>

typedef struct zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} zem_t;

void zem_init(zem_t *zem, int value) {
    zem->value = value;
    pthread_cond_init(&zem->cond, nullptr);
    pthread_mutex_init(&zem->mutex, nullptr);
}

void zem_wait(zem_t *zem) {
    pthread_mutex_lock(&zem->mutex);
    while (zem->value <= 0) {
        pthread_cond_wait(&zem->cond, &zem->mutex);
    }
    zem->value--;
    pthread_mutex_unlock(&zem->mutex);
}

void zem_post(zem_t *zem) {
    pthread_mutex_lock(&zem->mutex);
    zem->value++;
    pthread_cond_signal(&zem->cond);
    pthread_mutex_unlock(&zem->mutex);
}