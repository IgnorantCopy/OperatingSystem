//
// Created by Ignorant on 2025/2/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        char *args[3];
        args[0] = strdup("wc");
        args[1] = strdup("../../Lesson02/p4.c");
        args[2] = NULL;
        execvp(args[0], args);
    } else {
        int wc = wait(NULL);
        assert(wc >= 0);
    }
    return 0;
}