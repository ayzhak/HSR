#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "limits.h"
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096

int
main(int argc, char ** argv) {
    if(argc <= 2) {
        puts("We need two arguments.");
        return 1;
    }
    
    FILE * src = fopen(argv[1], "r");
    FILE * dst = fopen(argv[2], "w");
    
    int c;

    do
    {
        c = fgetc (src);

        if (c == EOF)
            break;

        fputc (c, dst);
    }
    while (1);
          
    fclose(src);
    fclose(dst);
}
