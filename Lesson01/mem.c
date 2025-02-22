//
// Created by Ignorant on 2025/2/18.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"


/*
 * 关闭地址空间随机化：
 *  echo 0 > /proc/sys/kernel/randomize_va_space
 * 0 - 关闭地址空间随机化
 * 1 - 半随机。共享库、栈、mmap() 以及 VDSO 将被随机化。
 * 2 - 全随机。除了 1 中所述，还有heap。
 */

int main(int argc, char *argv[]) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) memory address of p: %08x\n", getpid(), (unsigned) p);
    *p = argc != 2 ? 0 : atoi(argv[1]);
    while (1) {
        Spin(1);
        (*p)++;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;
}
