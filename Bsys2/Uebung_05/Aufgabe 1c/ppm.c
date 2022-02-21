#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "ppm.h"
#include "image.h"

/**
 * Internal module support structures
 */
typedef struct
{
    image_t i;
    FILE * file_stream;
    rgb_t buffer[];
} ppm_image_t;

/**
 * Internal module support constants
 */
static char const * const ppm_file_header = "P3\n%d %d\n255\n";

/**
 * Internal module functions
 */
static void write_ppm_pixel (ppm_image_t * image, int x, int y, rgb_t color)
{
    image->buffer[y * image->i.size + x] = color;
}

static void close_ppm_image (ppm_image_t * image)
{
    for (int row = 0; row < image->i.size; ++row)
        {
            for (int col = 0; col < image->i.size; ++col)
                {
                    rgb_t color = image->buffer[row * image->i.size + col];
                    fprintf (image->file_stream, "%d %d %d ", color.red, color.green, color.blue);
                }
            fprintf (image->file_stream, "\n");
        }

    fclose (image->file_stream);
    free (image);
}

/**
 * Module API functions
 */
image_t * open_ppm_image (char const * filename, uint32_t size)
{
    ppm_image_t * image = malloc (sizeof(ppm_image_t) + sizeof(rgb_t[size * size]));
    image->i.size = size;
    image->i.set_pixel = (set_pixel_func_t) write_ppm_pixel;
    image->i.close = (close_image_func_t) close_ppm_image;
    image->file_stream = fopen (filename, "w+");

    fprintf (image->file_stream, ppm_file_header, size, size);

    return (image_t*) image;
}
