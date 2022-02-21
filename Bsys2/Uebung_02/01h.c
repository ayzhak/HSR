#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void
print_env (void)
{
    printf ("&environ = %p, environ = %p\n", &environ, environ);
    
    for (char **p = environ; *p; ++p)
    {
        printf ("*(%p) = %p : %s\n", p, *p, *p);
    }
    
    printf ("----------------------\n");
}


int
main (int argc, char **argv)
{
    print_env ();
    putenv ("BSYS_HOME=home");
    print_env ();
    putenv ("BSYS_HOME=bsys");
    print_env ();
    setenv("BSYS_HOME", "bsys", 1);
    print_env ();
    return 0;
}
