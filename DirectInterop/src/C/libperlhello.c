#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

int hello_from_perl(int argc, char **argv, char **env)
{
    char *embedding[] = { "", "-e", "0", NULL };

    PERL_SYS_INIT3(&argc,&argv,&env);
    my_perl = perl_alloc();
    perl_construct( my_perl );

    perl_parse(my_perl, NULL, 3, embedding, NULL);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
    perl_run(my_perl);

    /** Treat $a as an integer **/
    eval_pv("$perlHello = 'Hello from perl! As simple function.'; print $perlHello", TRUE);

    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();

    return 0;
}
