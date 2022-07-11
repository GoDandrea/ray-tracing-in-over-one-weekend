#include "rtweekend.h"

#include "color.h"
#include "body_list.h"
#include "sphere.h"

#include <iostream>

#define WHITE color(1,1,1)
#define SKY_BLUE color(0.5,0.7,1.0)
#define RED color(1,0,0);


color ray_color(const ray &r, const body &world) {
    
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + WHITE);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)*WHITE + t*SKY_BLUE;
}


int main() {

    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int image_channels = 3;

    unsigned char image_data[image_width * image_height * image_channels];
    int index = 0;


    // World
    body_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 
                                    - vec3(0, 0, focal_length);


    // Render
    for (int j = image_height-1; j >= 0; --j) {
        
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
        
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

            color pixel_color = ray_color(r, world);
            
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
