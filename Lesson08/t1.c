//
// Created by Ignorant on 2025/4/22.
//


#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;

void *my_thread(void *arg) {
    printf("%s: begin\n", (char *)arg);
    for (int i = 0; i < 1e7; i++) {
        // critical section
        counter++;
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}

int main() {
    pthread_t p1;
    pthread_t p2;
    printf("main: begin (counter = %d)\n", counter);
    pthread_create(&p1, nullptr, my_thread, "A");
    pthread_create(&p2, nullptr, my_thread, "B");
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    printf("main: done with both threads (counter = %d)\n", counter);
    return 0;
}
