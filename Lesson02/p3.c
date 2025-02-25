//
// Created by Ignorant on 2025/2/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    printf("hello world (pid: %d)\n", getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid: %d)\n", getpid());
        char *args[3];
        args[0] = strdup("wc");     // word count 程序: 统计文件的行数、字数、字节数
        args[1] = strdup("../../Lesson02/p3.c");    // wc 程序的参数，这里是 p3.c 文件
        args[2] = NULL;
        execvp(args[0], args);
        printf("This line should not be printed\n");
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, getpid());
    }
    return 0;
}