#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#include "pbm.h"
#include "image.h"

/**
 * Internal module support structures
 */
typedef struct
{
    image_t i;
    FILE * file_stream;
    rgb_t buffer[];
} pbm_image_t;

/**
 * Internal module support constants
 */
static char const * const pbm_file_header = "P6\n%d %d\n255\n";

/**
 * Internal module functions
 */
static void write_pbm_pixel (pbm_image_t * image, int x, int y, rgb_t color)
{
    image->buffer[y * image->i.size + x] = color;
}


static void close_pbm_image (pbm_image_t * image)
{
    fwrite (image->buffer, image->i.size * image->i.size, sizeof(rgb_t), image->file_stream);

    fclose (image->file_stream);
    free (image);
}


/**
 * Module API functions
 */
image_t * open_pbm_image (char const * filename, uint32_t size)
{
    pbm_image_t * image = malloc (sizeof(pbm_image_t) + sizeof(rgb_t[size * size]));
    image->i.size = size;
    image->i.set_pixel = (set_pixel_func_t) write_pbm_pixel;
    image->i.close = (close_image_func_t) close_pbm_image;
    image->file_stream = fopen (filename, "w+");

    fprintf (image->file_stream, pbm_file_header, size, size);

    return (image_t*) image;
}
