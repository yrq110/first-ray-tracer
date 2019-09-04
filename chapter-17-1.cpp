//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"
#include "base/sphere.h"
#include "base/hitable_list.h"
#include "base/camera.h"
#include "base/material.h"
#include "base/random.h"
#include "base/moving_sphere.h"
#include "base/texture.h"
#include "base/surface_texture.h"
#include "base/aarect.h"

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return emitted + attenuation*color(scattered, world, depth+1);
        }
        else {
            // return vec3(0,0,0);
            return emitted;
        }
    }
    else {
        return vec3(0, 0, 0);
        // vec3 unit_direction = unit_vector(r.direction());
        // float t = 0.5*(unit_direction.y() + 1.0);
        // return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

hitable *simple_light() {
    texture *pertext = new noise_texture(5);
    hitable **list = new hitable*[4];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
    list[2] = new sphere(vec3(0, 7, 0), 2, new diffuse_light(new constant_texture(vec3(4,4,4))));
    list[3] = new xy_rect(3, 5, 1, 3, -2, new diffuse_light(new constant_texture(vec3(4,4,4))));
    return new hitable_list(list, 4);
}

int main() {
    int nx = 800;
    int ny = 400;
    int ns = 10;
    int index = 0;
    int channel_num = 3;
    unsigned char data[nx * ny * channel_num];
    // std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    // hitable *world = two_perlin_spheres();
    hitable *world = simple_light();

    vec3 lookfrom(13,2,5);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, vec3(0,1,0), 50, float(nx)/float(ny), aperture, dist_to_focus, 0.0, 1.0);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world,0);
            }
            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            // std::cout << ir << " " << ig << " " << ib << "\n";
            data[index++] = ir;
            data[index++] = ig;
            data[index++] = ib;
        }
    }
    stbi_write_png("chapter-17-1.png", nx, ny, channel_num, data, 0);
}
