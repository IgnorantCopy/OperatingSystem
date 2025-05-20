//
// Created by root on 5/20/25.
//


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char *proc_info = "Hello World!";
pthread_mutex_t proc_info_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    printf("t1: before check\n");
    pthread_mutex_lock(&proc_info_mutex);
    if (proc_info) {
        printf("t1: after check\n");
        sleep(2);
        printf("t1: use!\n");
        printf("%s\n", proc_info);
    }
    pthread_mutex_unlock(&proc_info_mutex);
    return NULL;
}

void *thread2(void *arg) {
    printf("\t\t\t\tt2: begin\n");
    sleep(1);
    pthread_mutex_lock(&proc_info_mutex);
    printf("\t\t\t\tt2: set to NULL\n");
    proc_info = nullptr;
    pthread_mutex_unlock(&proc_info_mutex);
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t p1, p2;
    printf("main: begin\n");
    pthread_create(&p1, nullptr, thread1, NULL);
    pthread_create(&p2, nullptr, thread2, NULL);
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    printf("main: end\n");
    return 0;
}

