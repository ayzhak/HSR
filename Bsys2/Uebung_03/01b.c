#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "limits.h"
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096

int
read_and_compare_one_block (
    int fd1,
    int fd2,
    char * buffer1,
    char * buffer2,
    size_t size
) {
    ssize_t read_bytes1 = read(fd1, buffer1, size);
    ssize_t read_bytes2 = read(fd2, buffer2, size);
    
    if(read_bytes1 != read_bytes2) {return -1;}
    
    if(memcmp(buffer1, buffer2, read_bytes1) != 0) {return -1;}
    
    return read_bytes1;
}

read_and_compare(    
    int fd1,
    int fd2
){
    char * buffer1 = malloc(BUFFER_SIZE);
    char * buffer2 = malloc(BUFFER_SIZE);

    ssize_t size = BUFFER_SIZE;
    
    while(size == BUFFER_SIZE) {
        size = read_and_compare_one_block(fd1, fd2, buffer1, buffer2, BUFFER_SIZE);
    }

    free(buffer1);
    free(buffer2);

    return (size > 0) - 1;
}

int
main(int argc, char ** argv) {
    if(argc <= 2) {
        puts("We need two arguments.");
        return 1;
    }
    
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);

    
    printf("Result: %d\n", read_and_compare(fd1, fd2));
        
    close(fd1);
    close(fd2);

}
