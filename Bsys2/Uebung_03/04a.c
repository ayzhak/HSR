#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "limits.h"
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096

int
main(int argc, char ** argv) {
    if(argc <= 1) {
        puts("We need one arguments.");
        return 1;
    }
    
    FILE * src = fopen(argv[1], "r");
    int lines = 0;
    char c;
    do {
        c = fgetc(src);
        
        if(c == EOF) {
            break;
        }
        
        if(c == '\n') {
            lines++;
        }
        
    } while (1);   
    
    printf("Lines: %d\n", lines);
    
    fclose(src);
}
