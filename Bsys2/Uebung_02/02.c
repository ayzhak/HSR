#include <stdio.h>
#include <string.h>

int
main (int argc, char **argv)
{
    for(int **p = argv; *p; p++) {    
        if(argc > 1 && !strcmp(*p,"-Bsys2")){
            printf("Richtig\n");
            if(*p < argv[argc - 1]) {
                puts(*(++p));
            } 
            else 
            {
                puts("No more arguments.");
            }
            return;
        }
    }
    printf("Falsch\n");
    return;
}


