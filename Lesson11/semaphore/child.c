//
// Created by root on 5/13/25.
//

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s);
    return nullptr;
}

int main(int argc, char* argv[]) {
    sem_init(&s, 0, 0);
    printf("parent: begin\n");
    pthread_t c;
    pthread_create(&c, nullptr, child, nullptr);
    sem_wait(&s);
    printf("parent: end\n");
    return 0;
}