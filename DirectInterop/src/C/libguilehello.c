#include <stdio.h>
#include <libguile.h>

SCM hello_from_guile(int argc, char ** argv) {

    SCM guileHello;                     // register guile function loaded from script file
    scm_init_guile();                   // initialize guile interpreter

    // Helper variable Cstring definitions
    char code[] = "(display \"Hello from Guile! As simple function.\")";
    char newline[] = "(newline)";

    char filename[] = "scripts/helloGuile.scm";

    scm_c_eval_string(code);           // this function evluates C-style defined string as Guile scheme code. Without C, it expects an SCM object.
    scm_c_eval_string(newline);        // not working, probably because stdout does not pick this when it is in library ... ?

    printf("\n");

    scm_c_primitive_load(filename);    // this function accepts path to file, again defined as a C string

    guileHello = scm_variable_ref(scm_c_lookup("guile-hello")); // lookup returns veriable bound to symbol provided in its arguent; reference dereferences its value and returns it
    scm_call_0(guileHello);           // calls `guile-hello` function defined with 0 arguments

    return 0;
}
