#ifndef COLOR_H
#define COLOR_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"

#include <iostream>


void write_color(unsigned char *image_data, color pixel_color, int index, int samples_per_pixel) {

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide color by number of samples
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each component
    image_data[index+0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    image_data[index+1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    image_data[index+2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
}

#endif
