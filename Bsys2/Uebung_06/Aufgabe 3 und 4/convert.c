#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.h"

char * convert_int_to_string (unsigned int number)
{
    int length = (number > 0 ? log10(number) + 1 : 1) + 1;
    char * string = malloc(length);
    snprintf(string, length, "%d", number);
    return string;
}

char * convert_double_to_string (double number)
{
    char * string = malloc(10);
    snprintf(string, 10, "%f", number);
    return string;
}

char * convert_int_to_env (char * name, unsigned int number)
{
    int length = strlen(name) + 1 + (number > 0 ? log10(number) + 1 : 1) + 1;
    char * string = malloc(length);
    snprintf(string, length, "%s=%d", name, number);
    return string;
}

char * convert_double_to_env (char * name, double number)
{
    int length = strlen(name) + 1 + 10;
    char * string = malloc(length);
    snprintf(string, length, "%s=%f", name, number);
    return string;
}

char * convert_string_to_env (char * name, char const * value)
{
    int length = strlen(name) + 1 + strlen(value) + 1;
    char * string = malloc(length);
    snprintf(string, length, "%s=%s", name, value);
    return string;
}


