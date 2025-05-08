//
// Created by Ignorant on 2025/4/22.
//


#include <stdio.h>
#include <pthread.h>
#include <assert.h>

void *my_thread(void *arg) {
    printf("%s\n", (char *)arg);
    return NULL;
}

int main() {
    pthread_t p1;
    pthread_t p2;
    printf("main: begin\n");
    int rc = pthread_create(&p1, nullptr, my_thread, "A");
    assert(rc == 0);
    rc = pthread_create(&p2, nullptr, my_thread, "B");
    assert(rc == 0);
    // join waits for the thread to finish
    rc = pthread_join(p1, nullptr);
    assert(rc == 0);
    rc = pthread_join(p2, nullptr);
    assert(rc == 0);
    printf("main: end\n");
    return 0;
}
