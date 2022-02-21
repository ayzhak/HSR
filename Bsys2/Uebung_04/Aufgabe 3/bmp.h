#ifndef BMP_H_
#define BMP_H_

#include "image.h"
#include <stddef.h>

image_t * open_bmp_image (char const * filename, uint32_t size);

#endif
