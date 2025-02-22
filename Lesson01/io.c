//
// Created by Ignorant on 2025/2/18.
//


#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

int main() {
    int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd >= 0);
    int rc = write(fd, "Hello, world!\n", 14);
    assert(rc == 14);
    close(fd);
    return 0;
}
