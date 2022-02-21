#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>

#define SIZE 256

// TODO: rgb_t
typedef struct  
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;

// TODO: window_t

typedef struct
{
    double center_x;
    double center_y;
    double size;
} window_t;

struct image;

typedef void (*set_pixel_func_t) (struct image*, int, int, rgb_t);
typedef void (*close_image_func_t) (struct image*);
typedef void (*merge_corners_func_t) (struct image*,
                                      char const * upper_left, char const * upper_right,
                                      char const * lower_left, char const * lower_right);

typedef struct image
{
    set_pixel_func_t set_pixel;
    close_image_func_t close;
    merge_corners_func_t merge_corners;
    uint32_t size;
} image_t;

// TODO: open_image_func_t

image_t open_image_func_t (char const filename, int size);

#endif /* IMAGE_H_ */
