//
// Created by Ignorant on 2025/2/19.
//


#include <stdio.h>

static char buff[256];
static char *string;

int main() {
    printf("Enter a string: ");
    gets(string);
    printf("You entered: %s\n", string);
    return 0;
}
