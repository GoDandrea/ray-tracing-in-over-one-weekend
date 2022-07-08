#ifndef COLOR_H
#define COLOR_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"

#include <iostream>


void write_color(unsigned char *image_data, color pixel_color, int index) {
    image_data[index+0] = static_cast<int>(255.999 * pixel_color.x());
    image_data[index+1] = static_cast<int>(255.999 * pixel_color.y());
    image_data[index+2] = static_cast<int>(255.999 * pixel_color.z());
}

#endif
