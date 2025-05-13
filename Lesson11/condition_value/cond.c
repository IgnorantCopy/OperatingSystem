//
// Created by root on 5/13/25.
//

#include <pthread.h>
#include <stdio.h>

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void *child(void *arg) {
    printf("child\n");
    thr_exit();
    return nullptr;
}

void thr_join() {
    pthread_mutex_lock(&m);
    while (!done) { // better than if
        pthread_cond_wait(&c, &m);
    }
    pthread_mutex_unlock(&m);
}

int main(int argc, char* argv[]) {
    printf("parent: begin\n");
    pthread_t c;
    pthread_create(&c, nullptr, child, nullptr);
    thr_join();
    printf("parent: end\n");
    return 0;
}
