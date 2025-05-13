//
// Created by root on 5/13/25.
//

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t mutex;
volatile int counter = 0;

void *child(void *arg) {
    for (int i = 0; i < 10000000; i++) {
        sem_wait(&mutex);
        counter++;
        sem_post(&mutex);
    }
    return nullptr;
}

int main(int argc, char* argv[]) {
    sem_init(&mutex, 0, 1);
    pthread_t c1;
    pthread_t c2;
    pthread_create(&c1, nullptr, child, nullptr);
    pthread_create(&c2, nullptr, child, nullptr);
    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    printf("result: %d (should be 20000000)\n", counter);
    return 0;
}
