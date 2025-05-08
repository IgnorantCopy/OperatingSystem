//
// Created by Ignorant on 2025/4/22.
//


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} arg_t;

typedef struct {
    int x;
    int y;
} ret_t;

void *my_thread(void *arg) {
    arg_t const *m = (arg_t *)arg;
    printf("%d %d\n", m->a, m->b);
    // 动态分配，使内存分配在堆上
    ret_t *r = malloc(sizeof(ret_t));
    r->x = m->a + m->b;
    r->y = m->a - m->b;
    return r;
}

int main() {
    pthread_t pthread;
    arg_t arg = {10, 20};
    ret_t *result;
    pthread_create(&pthread, nullptr, my_thread, &arg);
    pthread_join(pthread, (void **)&result);
    printf("returned %d %d\n", result->x, result->y);
    return 0;
}
