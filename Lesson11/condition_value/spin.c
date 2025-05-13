//
// Created by root on 5/13/25.
//

#include <pthread.h>
#include <stdio.h>

volatile int done = 0;

void *child(void *arg) {
    printf("child\n");
    done = 1;
    return nullptr;
}

int main(int argc, char* argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    pthread_create(&c, nullptr, child, nullptr);
    while (done == 0) {}
    printf("parent: end\n");
    return 0;
}
