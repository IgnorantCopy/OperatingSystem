//
// Created by Ignorant on 2025/2/18.
//

#ifndef OPERATINGSYSTEM_COMMON_H
#define OPERATINGSYSTEM_COMMON_H
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

double GetTime() {
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) t.tv_sec + (double) t.tv_usec/1e6;
}

void Spin(int seconds) {
    double t = GetTime();
    while ((GetTime() - t) < (double) seconds); // do nothing in loop
}

#endif //OPERATINGSYSTEM_COMMON_H
