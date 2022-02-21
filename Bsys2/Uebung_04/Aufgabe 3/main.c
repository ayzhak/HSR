#include "bmp.h"
#include "julia.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t spawn_worker (
    char const * filename,
    uint32_t image_size,
    window_t window, 
    double exponent,
    double real,
    double imaginary,
    int iterations
) {
    pid_t pid = fork();
    if(pid == 0) {
        image_t * image = open_bmp_image(filename, image_size);
        calculate_julia(image, window, exponent, real, imaginary, iterations);
        image->close(image);
        exit(EXIT_SUCCESS);
    } else {
        return pid;
    }
}

int main() {
    char const * const upper_left_filename = "upper_left.bmp"; 
    char const * const upper_right_filename = "upper_right.bmp"; 
    char const * const lower_left_filename = "lower_left.bmp";
    char const * const lower_right_filename = "lower_right.bmp"; 
    char const * const merged_image_filename = "julia.bmp";

    uint32_t const image_size = 1600;

    double const exponent = 2.0; 
    double const real = 0.0;
    double const imaginary = -1.0; 
    int const iterations = 100;

    spawn_worker (upper_left_filename, image_size / 2, (window_t) { 0.5, 0.5, 0.5 }, exponent, real, imaginary, iterations);
    spawn_worker (upper_right_filename, image_size / 2, (window_t) { -0.5, 0.5, 0.5 }, exponent, real, imaginary, iterations);
    spawn_worker (lower_left_filename, image_size / 2, (window_t) { 0.5, -0.5, 0.5 }, exponent, real, imaginary, iterations);
    spawn_worker (lower_right_filename, image_size / 2, (window_t) { -0.5, -0.5, 0.5 }, exponent, real, imaginary, iterations);

    pid_t child;
    while ((child = wait (NULL)) > 0)
    {
        printf ("Child with PID %d finished\n", child);
    }

    image_t * output_image = open_bmp_image (merged_image_filename, image_size);
    output_image->merge_corners (output_image, upper_left_filename, upper_right_filename, lower_left_filename, lower_right_filename);
    output_image->close (output_image);
}