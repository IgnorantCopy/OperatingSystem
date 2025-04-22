//
// Created by Ignorant on 2025/4/22.
//


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *noParameter(void *args) {
    printf("Hello\n");
    for (int i = 0; i < 5e7; i++) {
        puts("Hello");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        const int rc = pthread_create(&tid[i], nullptr, noParameter, NULL);
        if (rc) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(-1);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        const int rc = pthread_join(tid[i], nullptr);
        if (rc) {
            fprintf(stderr, "Error joining thread %d\n", i);
        }
    }
    return 0;
}
