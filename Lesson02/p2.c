//
// Created by Ignorant on 2025/2/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("hello world (pid: %d)\n", getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {   // 子进程
        printf("hello, I am child (pid: %d)\n", getpid());
    } else {    // 父进程
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, getpid());
    }
    return 0;
}
