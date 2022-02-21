#include "bmp.h"

#define SIZE 256

void paint_background(image_t * image)
{
    for (int y = 0; y < SIZE; y++) {      // 1.
        for (int x = 0; x < SIZE; x++) {  // 1.

            int r = 255 - y;              // 2.
            int g = x;                    // 2.
            int b = (x + y) / 2;          // 2.

            rgb_t color = {r, g, b};      // 3.

            image->set_pixel (image, x, y, color);  // 4.
        }
    }
}


int main ()  // (d)
{
    image_t * image = open_bmp_image ("gradient.bmp", SIZE); 
    paint_background (image); 
    image->close (image);
}