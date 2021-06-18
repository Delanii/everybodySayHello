#include <stdio.h>

int hello_from_rust();
int hello_from_lua();
int hello_from_python();
int hello_from_guile();
int hello_from_perl();
int hello_from_cpp();

void haskellHelloLibInit();
void hello_from_haskell();
void haskellHelloLibExit();

void hello_from_java();

int main() {
    char langName[] = "C";

    // First say "Hello" from C itself:

    printf("\nHello from %s!\n\n", langName);
    fflush(stdout); // Should print first message immediately, not after "Rust hello," as it happens when testing with make

    // Next goes Rust

    hello_from_rust();
    fflush(stdout);

    // Third is lua, this time through Rust `mlua` crate

    hello_from_lua();
    fflush(stdout);

    hello_from_python();
    fflush(stdout);

    hello_from_guile();
    fflush(stdout);

    hello_from_perl();
    fflush(stdout);

    hello_from_cpp();
    fflush(stdout);

    haskellHelloLibInit();
    hello_from_haskell();
    haskellHelloLibExit();
    fflush(stdout);

    printf("\n");
    hello_from_java();

    printf("\n\nDone!\n");

    return 0;
}
