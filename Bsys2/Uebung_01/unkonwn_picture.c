#include <stdio.h>
#include "bmp.h"
#include "image.h"
#include "pixel_data.h"

#define SIZE 256


rgb_t color_table[4] = {
    {0x0, 0x0, 0x0},
    {0x8C, 0x18, 0x5F},
    {0xD7, 0x24, 0x65},
    {0x0, 0x0, 0x0}    
};

void paint_white(image_t * image)
{
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            rgb_t color = {255,255,255};
            image->set_pixel (image, x, y, color);
        }
    }
}


void paint_pixel(image_t * image)
{
    size_t size = sizeof(pixel_data) / sizeof(pixel_data[0]);
    for(unsigned int x = 0; x < size; x++)
    {
        short value =  pixel_data[x];
        short x = value >> 7;
        short y = value >> 2 << 8 >> 8;
        short index = value << 13;
        printf("x = %d, y = %d, index = %d", x, y, index);
        image->set_pixel(image, -x, y, color_table[index]);
    }
}

int main ()  // (d)
{
    image_t * image = open_bmp_image ("gradient.bmp", SIZE); 
    paint_white (image);
    paint_pixel(image);
    image->close (image);
}