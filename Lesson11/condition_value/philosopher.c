//
// Created by root on 5/20/25.
//


#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FORKS 5


sem_t forks[NUM_FORKS];

int left(const int p) { return p; }

int right(const int p) { return (p + 1) % NUM_FORKS; }

void get_forks(const int p) {
    if (p % 2 == 0) {
        sem_wait(&forks[left(p)]);
        sleep(1);
        sem_wait(&forks[right(p)]);
    } else {
        sem_wait(&forks[right(p)]);
        sleep(1);
        sem_wait(&forks[left(p)]);
    }
}

void put_forks(const int p) {
    if (p % 2 == 0) {
        sem_post(&forks[left(p)]);
        sleep(1);
        sem_post(&forks[right(p)]);
    } else {
        sem_post(&forks[right(p)]);
        sleep(1);
        sem_post(&forks[left(p)]);
    }
}

void philosopher(const int p) {
    while (true) {
        printf("philosopher %d is thinking...\n", p);
        sleep(1);
        get_forks(p);
        sleep(1);
        printf("philosopher %d is eating...\n", p);
        sleep(1);
        put_forks(p);
        sleep(1);
    }
}

int main(int argc, char* argv[]) {
    for (int i = 0; i < NUM_FORKS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    pthread_t philosophers[NUM_FORKS];
    for (int i = 0; i < NUM_FORKS; i++) {
        pthread_create(&philosophers[i], nullptr, philosopher, (void*)i);
    }
    while (true) {}
    return 0;
}
