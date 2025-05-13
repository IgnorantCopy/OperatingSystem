//
// Created by root on 5/13/25.
//

#include <pthread.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE (4 * 1024 * 1024)

int bytesLeft = MAX_HEAP_SIZE;

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *allocate(const int size) {
    pthread_mutex_lock(&m);
    while (bytesLeft < size) {
        pthread_cond_wait(&c, &m);
    }
    void *ptr = malloc(size);
    bytesLeft -= size;
    pthread_mutex_unlock(&m);
    return ptr;
}

void free(void *ptr, const int size) {
    pthread_mutex_lock(&m);
    bytesLeft += size;
    pthread_cond_signal(&c);    // pthread_cond_broadcast()
    pthread_mutex_unlock(&m);
}

int main(int argc, char* argv[]) {

    return 0;
}
