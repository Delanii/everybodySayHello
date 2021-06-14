#include <stdio.h>

int hello_from_rust();
int hello_from_lua();
int hello_from_python();
int hello_from_guile();
int hello_from_perl();

int main() {
    char langName[] = "C";

    // First say "Hello" from C itself:

    printf("\nHello from %s!\n\n", langName);
    fflush(stdout); // Should print first message immediately, not after "Rust hello," as it happens when testing with make

    // Next goes Rust

    hello_from_rust();

    // Third is lua, this time through Rust `mlua` crate

    hello_from_lua();

    hello_from_python();

    hello_from_guile();

    hello_from_perl();

    printf("\nDone!\n");

    return 0;
}
