//
// Created by root on 5/13/25.
//

#include <semaphore.h>
#include <stdio.h>

typedef struct _rwlock_t {
    sem_t lock;
    sem_t write;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->write, 0, 1);
}

void rwlock_acquire_read(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1) {
        sem_wait(&rw->write);
    }
    sem_post(&rw->lock);
}

void rwlock_release_read(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0) {
        sem_post(&rw->write);
    }
    sem_post(&rw->lock);
}

void rwlock_acquire_write(rwlock_t *rw) {
    sem_wait(&rw->write);
}

void rwlock_release_write(rwlock_t *rw) {
    sem_post(&rw->write);
}

int read_loops;
int write_loops;
int counter = 0;

rwlock_t mutex;

void *reader(void *arg) {
    int local = 0;
    for (int i = 0; i < read_loops; i++) {
        rwlock_acquire_read(&mutex);
        local = counter;
        rwlock_release_read(&mutex);
        printf("read %d\n", local);
    }
    printf("read done: %d\n", local);
    return nullptr;
}

void *writer(void *arg) {
    for (int i = 0; i < write_loops; i++) {
        rwlock_acquire_write(&mutex);
        counter++;
        rwlock_release_write(&mutex);
    }
    printf("write done\n");
    return nullptr;
}

int main(int argc, char* argv[]) {

    return 0;
}
