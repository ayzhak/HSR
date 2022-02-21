#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "julia.h"

int main (int argc, char ** argv)
{
    if (argc != 2)
    {
        printf ("Usage: %s <output_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char const * const filename = argv[1];
    printf ("Rendering Julia set into '%s'...", filename);
    fflush (stdout);
    image_t * image = open_bmp_image (filename, 800);
    calculate_julia (image, (window_t ) { 0.0, 0.0, 1.0 }, 2.0, 0.0, -1.0, 100);
    image->close(image);
    puts ("Done");
}
