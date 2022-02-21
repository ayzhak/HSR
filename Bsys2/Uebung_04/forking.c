#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>

void print_pids(char * word) {
    printf("PID\t%d:\t%s\n", getpid(), word);
    printf("PID\t%d:\tMy parent's PID is %d.\n", getpid(), getppid());
}

void execute_parent_code(void) {
    print_pids("I am the parent process");
    int status;
    pid_t wpid = wait (&status);
    printf("PID\t%d:\tChild %d exited with statuscode: %d\n", getpid(), wpid, WEXITSTATUS(status));
    sleep(10);
    printf("PID\t%d:\tExiting.\n", getpid());
}

void execute_child_code(void) {
    print_pids("I am the child process");
    printf("PID\t%d:\tExiting.\n", getpid());
    exit(EXIT_FAILURE);
}

void handle_at_exit(void) {
    printf("PID\t%d:\tI'am a really bad boy\n", getpid());
}

int main(void) {
    pid_t pid = fork();

    if(pid == 0) {
        atexit(handle_at_exit);
        execute_child_code();
        return EXIT_SUCCESS;
    } else {
        execute_parent_code();
    }
    return 0;
}