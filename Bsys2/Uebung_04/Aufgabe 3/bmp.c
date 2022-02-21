#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bmp.h"
#include "image.h"


/**
 * Internal module support structures
 */
typedef struct __attribute__((__packed__))
{
    char type[2];
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} bmp_file_header_t;

typedef struct __attribute__((__packed__))
{
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t color_map_entry_count;
    uint32_t significant_colors_count;
} bmp_image_header_t;

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} bgr_t;

typedef struct
{
    image_t i;
    int file_descriptor;
} bmp_image_t;

/**
 * Internal module support constants
 */
unsigned char const bmp_padding_bytes[3] = { 0, 0, 0 };
size_t const bmp_data_offset = sizeof(bmp_file_header_t) + sizeof(bmp_image_header_t);

/**
 * Internal module functions
 */
static int create_bmp_file (char const * filename, uint32_t size)
{
    int file_descriptor = open (filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IWOTH | S_IROTH);

    // Write BMP header to file
    bmp_file_header_t file_header;
    memcpy (file_header.type, "BM", 2);
    file_header.file_size = sizeof(bmp_file_header_t) + sizeof(bmp_image_header_t) + 4 * size * size;
    file_header.reserved1 = 0;
    file_header.reserved2 = 0;
    file_header.offset = sizeof(bmp_file_header_t) + sizeof(bmp_image_header_t);
    write (file_descriptor, &file_header, sizeof(file_header));

    // Write image header to file
    bmp_image_header_t image_header;
    image_header.header_size = sizeof(bmp_image_header_t);
    image_header.width = size;
    image_header.height = size;
    image_header.planes = 1;
    image_header.bits_per_pixel = 24;
    image_header.compression = 0;
    image_header.image_size = (size + (size % 4)) * size;
    image_header.x_pixels_per_meter = round (72.0 * 39.3701);
    image_header.y_pixels_per_meter = image_header.x_pixels_per_meter;
    image_header.color_map_entry_count = 0;
    image_header.significant_colors_count = 0;
    write (file_descriptor, &image_header, sizeof(image_header));

    return file_descriptor;
}

static void write_bmp_pixel (bmp_image_t *image, uint32_t x, uint32_t y, rgb_t color)
{
    uint32_t const size = image->i.size;
    off_t const row = size - 1 - y;
    off_t const row_length = size * sizeof(rgb_t) + size % 4;
    lseek (image->file_descriptor, sizeof(bmp_file_header_t) + sizeof(bmp_image_header_t) + row * row_length + x * 3, SEEK_SET);
    bgr_t bmp_color = { color.blue, color.green, color.red };
    write (image->file_descriptor, &bmp_color, sizeof(bmp_color));
    if (x == size - 1 && size % 4)
    {
        write (image->file_descriptor, bmp_padding_bytes, size % 4);
    }
}

static void close_bmp_image (bmp_image_t * image)
{
    close (image->file_descriptor);
    free (image);
}

static void merge_bmp_blocks (bmp_image_t * output, char const * left, char const * right)
{
    int size = output->i.size;
    uint8_t * row_buffer = malloc(3 * size / 2);

    int left_file = open(left, O_RDONLY);
    int right_file = open(right, O_RDONLY);
    lseek(left_file, bmp_data_offset, SEEK_SET);
    lseek(right_file, bmp_data_offset, SEEK_SET);

    for (off_t row = 0; row < size / 2; ++row)
    {
        read(left_file, row_buffer, 3 * size / 2);
        write(output->file_descriptor, row_buffer, 3 * size / 2);
        lseek(left_file, size / 2 % 4, SEEK_CUR);

        read(right_file, row_buffer, 3 * size / 2);
        write(output->file_descriptor, row_buffer, 3 * size / 2);
        lseek(right_file, size / 2 % 4, SEEK_CUR);

        write(output->file_descriptor, bmp_padding_bytes, size % 4);
    }

    free(row_buffer);

    close(left_file);
    close(right_file);
}

void merge_bmp_corners (bmp_image_t * output,
                        char const * upper_left, char const * upper_right,
                        char const * lower_left, char const * lower_right)
{
    merge_bmp_blocks(output, lower_left, lower_right);
    merge_bmp_blocks(output, upper_left, upper_right);
}

/**
 * Module API functions
 */
image_t * open_bmp_image (char const * filename, uint32_t size)
{
    bmp_image_t *image = malloc (sizeof(bmp_image_t));
    image->i.size = size;
    image->i.set_pixel = (set_pixel_func_t) write_bmp_pixel;
    image->i.close = (close_image_func_t) close_bmp_image;
    image->i.merge_corners = (merge_corners_func_t) merge_bmp_corners;
    image->file_descriptor = create_bmp_file (filename, size);

    return (image_t*) image;
}
