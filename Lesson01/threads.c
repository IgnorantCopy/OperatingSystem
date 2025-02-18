//
// Created by Ignorant on 2025/2/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"


/*
 * volatile 关键字：在多线程编程中保证数据的一致性
 *  1. 可见性：对一个 volatile 变量的写操作对于其他线程来说是可见的，即一个线程对变量的修改对其他线程是立即可见的。
 *  2. 有序性：volatile 变量的读写具有顺序性，即变量的写操作先于后续的读操作。
 * 需要注意的是，volatile关键字无法解决所有多线程并发访问的问题。它只能确保对变量的单个读/写操作具有可见性和有序性，并不能解决复合操作的原子性问题。
 * 对于复杂的操作，仍然需要使用其他的同步机制，如锁或原子类。
 */
volatile int counter = 0;
int loops = 0;

void* worker(void *arg) {
    for (int i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value: %d\n", counter);
    
    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    
    printf("Final value: %d\n", counter);
    return 0;
}
