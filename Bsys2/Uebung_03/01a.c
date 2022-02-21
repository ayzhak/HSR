#include "stdio.h"
#include "string.h"
#include "limits.h"
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char ** argv) {
    if(argc <= 2) {
        puts("We need two arguments.");
        return 1;
    }
    
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);
    
    close(fd1);
    close(fd2);
}
