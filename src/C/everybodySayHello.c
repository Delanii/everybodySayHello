#include <stdio.h>

void extern hello_from_rust();

int main(void) {
    char langName[] = "C";

    // First say "Hello" from C itself:

    printf("Hello from %s\n\n", langName);

    // Next goes Rust

    hello_from_rust();

    return 0;
}
