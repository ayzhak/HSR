#include <complex.h>

#include "julia.h"

static rgb_t const palette[16] = {
    { 66, 30, 15 },
    { 25, 7, 26 },
    { 9, 1, 47 },
    { 4, 4, 73 },
    { 0, 7, 100 },
    { 12, 44, 138 },
    { 24, 82, 177 },
    { 57, 125, 209 },
    { 134, 181, 229 },
    { 211, 236, 248 },
    { 241, 233, 191 },
    { 248, 201, 95 },
    { 255, 170, 0 },
    { 204, 128, 0 },
    { 153, 87, 0 },
    { 106, 52, 3 }
};

void
calculate_julia (image_t *image,
                 window_t window,
                 double exponent,
                 double real,
                 double imaginary,
                 int iterations)
{
    double complex const upper_left = (window.size - window.center_x) + ((window.size + window.center_y) * I);
    double complex const lower_right = (-window.size - window.center_x) + ((-window.size + window.center_y) * I);
    double const x_scaling_factor = (creal (upper_left) - creal (lower_right)) / (image->size - 1);
    double const y_scaling_factor = (cimag (upper_left) - cimag (lower_right)) / (image->size - 1);
    double complex const k = real + imaginary * I;

    for (unsigned int y = 0; y < image->size; ++y)
    {
        double complex c = (cimag (upper_left) - y * y_scaling_factor) * I;
        for (unsigned int x = 0; x < image->size; ++x)
        {
            c = creal (lower_right) + x * x_scaling_factor + cimag (c) * I;
            double complex z = c;

            rgb_t color = { 0, 0, 0 };
            for (int n = 0; n < iterations; ++n)
            {
                if (cabs (z) > 2)
                {
                    color = palette[n % 16];
                    break;
                }
                z = cpow (z, exponent) + k;
            }

            image->set_pixel (image, x, y, color);
        }
    }
}
