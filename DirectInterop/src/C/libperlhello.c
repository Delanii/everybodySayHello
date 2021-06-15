#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

int hello_from_perl(int argc, char **argv, char **env)
{
	
	// Machine spirit incantations to make perl interpreter run
	
    char *embedding[] = { "", "-e", "0", NULL };

    PERL_SYS_INIT3(&argc,&argv,&env);
    my_perl = perl_alloc();
    perl_construct( my_perl );

    perl_parse(my_perl, NULL, 3, embedding, NULL);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
    perl_run(my_perl);
    
	// Incantations finished, perl interpreter instance `my_perl` is running

    /** function `eval_pv` is used to evaluate perl code **/
    eval_pv("$perlHello = '\nHello from perl! As simple function.\n'; print $perlHello;", TRUE);

    printf("\n");

    // This loads perl script
	eval_pv("\
    $script = './scripts/helloPerl.pl';\
    do $script;",\
            TRUE);

    // Cleanup interpreter instances
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();

    return 0;
}
