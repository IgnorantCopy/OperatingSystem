//
// Created by root on 5/20/25.
//


#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int min_fd = 0;
int max_fd = 5;

int main(int argc, char* argv[]) {
    while (true) {
        // initialize the file descriptor set to all zeroes
        fd_set read_fds;
        FD_ZERO(&read_fds);

        // set the bits for the file descriptors
        for (int fd = min_fd; fd < max_fd; fd++) {
            FD_SET(fd, &read_fds);
        }

        // do the select
        int rc = select(max_fd + 1, &read_fds, nullptr, nullptr, nullptr);
        for (int fd = min_fd; fd < max_fd; fd++) {
            if (FD_ISSET(fd, &read_fds)) {
                // processFD(fd);
            }
        }
    }
    return 0;
}
