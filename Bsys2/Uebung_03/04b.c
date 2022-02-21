#include <stdio.h>
#include <ctype.h>

int
main (int argc, char **argv)
{
    if (argc != 2)
    {
        printf ("Usage: %s file\n", argv[0]);
        return 1;
    }

    FILE * file = fopen (argv [1], "r");

    int c;
    unsigned lines = 0;
    unsigned words = 0;

    int was_space = 0;

    do
    {
        c = fgetc (file);

        if (c == EOF)
            break;

        if (c == '\n')
        {
            ++lines;
        }

        int is_space = isspace (c);

        if (is_space && !was_space)
        {
            ++words;
        }

        was_space = is_space;
    }
    while (1);

    printf ("%d lines, %d words\n", lines, words);

    fclose (file);

    return 0;
}


