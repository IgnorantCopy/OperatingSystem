//
// Created by root on 5/13/25.
//

#include <pthread.h>
#include <stdio.h>

#define MAX 4

int buffer[MAX];
int fill = 0;
int use = 0;
int count = 0;

pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(const int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    count++;
}

int get() {
    const int temp = buffer[use];
    use = (use + 1) % MAX;
    count--;
    return temp;
}

void *producer(void *arg) {
    const int loops = (int) arg;
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while (count == MAX) {
            pthread_cond_wait(&empty, &mutex);
        }
        put(i);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void *consumer(void *arg) {
    const int loops = (int) arg;
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }
        int temp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("%d\n", temp);
    }
    return nullptr;
}

int main(int argc, char* argv[]) {

    return 0;
}
