//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

#include "color.h"
#include "vec3.h"

#include <iostream>


int main() {


    // Image

    const int image_width = 256;
    const int image_height = 256;
    const int image_channels = 3;

    unsigned char image_data[image_width * image_height * image_channels];
    int index = 0;


    // Render

    for (int j = image_height-1; j >= 0; --j) {
        
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
        
            color pixel_color(double(i)/(image_width-1), 
                              double(j)/(image_height-1), 
                              0.25);
            write_color(image_data, pixel_color, index);
            index += 3;
        }
    }

    stbi_write_png("image.png", 
                    image_width, 
                    image_height, 
                    image_channels, 
                    image_data,
                    image_width * image_channels);
    std::cerr << "\nDone.\n";
}
