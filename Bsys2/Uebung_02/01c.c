#include <stdio.h>

int
main (int argc, char **argv)
{
    for (char **p = argv; *p; ++p)
    {
        puts (*p);
    }

    return 0;
}


