//
// Created by root on 5/20/25.
//


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PR_STATE_INIT 0
#define PR_STATE_RUNNING 1
#define PR_STATE_EXITED 2

typedef struct {
    pthread_t tid;
    int state;
} pr_thread_t;

pthread_mutex_t mtLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mtCond = PTHREAD_COND_INITIALIZER;
int mtInit = 0;
pr_thread_t *mThread;

pr_thread_t *pr_create_thread(void *(*start_routine)(void *)) {
    pr_thread_t *p = malloc(sizeof(pr_thread_t));
    if (p == NULL) {
        return nullptr;
    }
    p->state = PR_STATE_INIT;
    pthread_create(&p->tid, nullptr, start_routine, nullptr);
    sleep(1);
    return p;
}

void pr_wait_thread(pr_thread_t *p) {
    pthread_join(p->tid, nullptr);
    free(p);
}

void *mMain(void *arg) {
    printf("mMain begin\n");
    pthread_mutex_lock(&mtLock);
    while (mtInit == 0) {
        pthread_cond_wait(&mtCond, &mtLock);
    }
    pthread_mutex_unlock(&mtLock);

    int mState = mThread->state;
    printf("mMain: state is %d\n", mState);
    return nullptr;
}

int main(int argc, char* argv[]) {
    printf("ordering: begin\n");
    mThread = pr_create_thread(mMain);

    pthread_mutex_lock(&mtLock);
    mtInit = 1;
    pthread_cond_signal(&mtCond);
    pthread_mutex_unlock(&mtLock);

    pr_wait_thread(mThread);
    printf("ordering: end\n");
    return 0;
}
