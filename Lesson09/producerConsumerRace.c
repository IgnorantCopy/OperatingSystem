//
// Created by Ignorant on 2025/4/29.
//


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NITER 10
#define BUFFER_SIZE 5

uint counter = 0;
uint in = 0;
uint out = 0;
int lock = 0;
int buffer[BUFFER_SIZE] = {0};

void *producer(void *arg) {
    for (int i = 0; i < NITER; i++) {
        printf("Counter in producer: %d\n", counter);
        int next_producer = rand() % 100 + 1;
        while (counter == BUFFER_SIZE) {}
        buffer[in] = next_producer;
        in = (in + 1) % BUFFER_SIZE;
        counter++;
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NITER; i++) {
        printf("Counter in consumer: %d\n", counter);
        while (counter == 0) {}
        int next_consumer = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        counter--;
    }
    return NULL;
}

int main() {
    pthread_t pro;
    pthread_t con;
    srand(time(nullptr));
    pthread_create(&pro, nullptr, producer, &pro);
    pthread_create(&con, nullptr, consumer, &con);
    pthread_join(pro, nullptr);
    pthread_join(con, nullptr);
    printf("Final: counter = %d\n", counter);
    return 0;
}
