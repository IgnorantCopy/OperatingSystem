//
// Created by Ignorant on 2025/3/18.
//

#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("location of code: %p\n", main);
    printf("location of code: %p\n", malloc(100e6));
    int a = 10;
    printf("location of stack: %p\n", &a);
    return 0;
}
