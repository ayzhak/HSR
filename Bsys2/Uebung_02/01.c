#include "stdio.h"
#include <stdlib.h>

char bsys_var[] = "BSYS_VAR=myvalue";

void print_value_of(char const * key) {
    char const * value = getenv(key);
    
    if(value) {
        printf ("Value of variable '%s' is: %s\n", key, value);
    } else {
        printf("Environment variable '%s' does not exist.\n", key);
    }
}

int main(void) {
    setenv("PATH", "nothing", 1);
    printf("REUTRN putenv: %d\n", putenv(bsys_var));
    bsys_var[9] = '_';
    bsys_var[10] = '_';
    
    print_value_of("PATH");
    print_value_of("path");
    print_value_of("BSYS_VAR");
    return 0;
}

