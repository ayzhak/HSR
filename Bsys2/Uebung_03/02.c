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
    
    char * buffer1 = malloc(BUFFER_SIZE);
    
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
    
    ssize_t read_bytes = BUFFER_SIZE;
    ssize_t write_bytes = BUFFER_SIZE;
    while(read_bytes == BUFFER_SIZE) {
        read_bytes = read(fd1, buffer1, BUFFER_SIZE);
        if(read_bytes < 0 ) {
            puts("Error on read");
            return -1;
        }
        write_bytes = write(fd2, buffer1, read_bytes);
        if(write_bytes < 0 ) {
            puts("Error on read");
            return -1;
        }
    }
      
       
    close(fd1);
    close(fd2);
    free(buffer1);
    return 0;

}
