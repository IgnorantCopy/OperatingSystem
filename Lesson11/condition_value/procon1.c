//
// Created by root on 5/13/25.
//

#include <assert.h>
#include <stdio.h>
#include <pthread.h>

int buffer;
int count = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(const int value) {
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get() {
    assert(count == 1);
    count = 0;
    return buffer;
}

void *producer(void *arg) {
    const int loops = (int) arg;
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        if (count == 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        put(i);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void *consumer(void *arg) {
    const int loops = (int) arg;
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        if (count == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        int temp = get();
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        printf("%d\n", temp);
    }
    return nullptr;
}

int main(int argc, char* argv[]) {

    return 0;
}
