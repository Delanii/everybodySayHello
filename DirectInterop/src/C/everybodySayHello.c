#include <stdio.h>

int hello_from_rust();
int hello_from_lua();

int main() {
    char langName[] = "C";

    // First say "Hello" from C itself:

    printf("\nHello from %s!\n\n", langName);

    // Next goes Rust

    hello_from_rust();

    // Third is lua, this time through Rust `mlua` crate

    hello_from_lua();

    printf("\nDone!\n");

    return 0;
}
