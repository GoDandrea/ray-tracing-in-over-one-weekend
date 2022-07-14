#include "rtweekend.h"

#include "color.h"
#include "body_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

#define WHITE color(1,1,1)
#define BLACK color(0,0,0)
#define SKY_BLUE color(0.5,0.7,1.0)
#define RED color(1,0,0)
#define LEMON color(0.8, 0.8, 0.0)
#define CLAY color(0.6, 0.4, 0.3)
#define SILVER color(0.8, 0.8, 0.8)
#define GOLD color(0.8, 0.6, 0.2)


color ray_color(const ray &r, const body &world, int depth) {
    
    hit_record rec;

    // After ray bounce limit, no more light is gathered
    if (depth <= 0)
        return BLACK;

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return BLACK;
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
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    int index = 0;
    const int image_channels = 3;
    unsigned char image_data[image_width * image_height * image_channels];


    // World
    body_list world;

    auto material_ground = make_shared<lambertian>(LEMON);
    auto material_center = make_shared<lambertian>(CLAY);
    auto material_left   = make_shared<metal>(SILVER);
    auto materal_right   = make_shared<metal>(GOLD);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.4), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.1,    0.0, -1.4), 0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.1,    0.0, -1.4), 0.5, materal_right));



    // Camera
    camera cam;


    // Render
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {

            color pixel_color(0,0,0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);

                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            
            write_color(image_data, pixel_color, index, samples_per_pixel);
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
