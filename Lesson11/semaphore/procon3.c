//
// Created by root on 5/13/25.
//

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define MAX 4

int buffer[MAX];
int fill = 0;
int use = 0;
int count = 0;

sem_t empty;
sem_t full;
sem_t mutex;

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
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
    return nullptr;
}

void *consumer(void *arg) {
    const int loops = (int) arg;
    for (int i = 0; i < loops; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        int temp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("%d\n", temp);
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    // ...
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    // ...
    return 0;
}