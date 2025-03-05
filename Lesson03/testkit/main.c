#include <stdio.h>
#include <string.h>
#include "testkit.h"

int main(int argc, const char *argv[]) {
    // Print all command line arguments.
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
}

int add(int a, int b) {
    return a + b;
}

UnitTest(test_simple) {
    assert(add(1, 2) == 3);
}

UnitTest(test_fail) {
    assert(114514 == 0x114514);
}

UnitTest(test_timeout) {
    while (1);
}

SystemTest(test_system, (const char *[]){"hello"}) {
    tk_assert(
        strstr(result->output, "hello") != NULL,
        "hello should appear in the output"
    );
}
