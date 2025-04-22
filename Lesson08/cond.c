//
// Created by Ignorant on 2025/4/22.
//


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ready = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *arg) {
    printf("Thread 1 is waiting...\n");
    pthread_mutex_lock(&lock);
    while (ready == 0) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread2(void *arg) {
    printf("Thread 2 is signaling...\n");
    pthread_mutex_lock(&lock);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, nullptr, thread1, NULL);
    sleep(1);
    pthread_create(&t2, nullptr, thread2, NULL);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    return 0;
}
