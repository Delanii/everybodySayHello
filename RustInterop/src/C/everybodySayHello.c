#include <stdio.h>

void extern hello_from_rust();
void extern hello_from_lua_through_rust();

int main(void) {
    char langName[] = "C";

    // First say "Hello" from C itself:

    printf("\nHello from %s!\n\n", langName);

    // Next goes Rust

    hello_from_rust();

    // Third is lua, this time through Rust `mlua` crate

    hello_from_lua_through_rust();

    printf("\nDone!\n");

    return 0;
}
