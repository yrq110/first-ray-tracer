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
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"
#include <iostream>
#include "base/sphere.h"
#include "base/hitable_list.h"
#include "base/camera.h"
#include "base/material.h"
#include "base/random.h"
#include "base/moving_sphere.h"
#include "base/texture.h"

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
             return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}


hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    // list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    texture *checker = new checker_texture( new constant_texture(vec3(0.2,0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    list[0] = new sphere(vec3(0, - 1000, 0), 1000, new lambertian(checker));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            
            float choose_mat = random_double();
            vec3 center(a+0.9*random_double(),0.2,b+0.9*random_double());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    // list[i++] = new sphere(
                    //     center, 0.2,
                    //     new lambertian(vec3(random_double()*random_double(),
                    //                         random_double()*random_double(),
                    //                         random_double()*random_double()))
                    // );
                    list[i++] = new moving_sphere(
                        center, center + vec3(0, 0.5*drand48(), 0),
                        0.0, 1.0,
                        0.2,
                        new lambertian(new constant_texture(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()))));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                        center, 0.2,
                        new metal(vec3(0.5*(1 + random_double()),
                                       0.5*(1 + random_double()),
                                       0.5*(1 + random_double())),
                                  0.5*random_double())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec3(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    // list[i++] = new sphere(vec3(0.3 0.2, .1), 10, even(t0), odd(t1)){}

    return new hitable_list(list,i);
}

// hitable *earth() {
//     int nx, ny, nn;
//     //unsigned char *tex_data = stbi_load("tiled.jpg", &nx, &ny, &nn, 0);
//     unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
//     material *mat =  new lambertian(new image_texture(tex_data, nx, ny));
//     return new sphere(vec3(0,0, 0), 2, mat);
// }

hitable *two_spheres() {
    texture * checker = new checker_texture( new constant_texture(vec3(0.2,0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
    int n = 50;
    hitable **list = new hitable*[n+1];
    // list[0] =  new sphere(vec3(0,-10, 0), 10, new lambertian( checker));
    // list[1] =  new sphere(vec3(0, 10, 0), 10, new lambertian( checker));
return new hitable_list(list,2);
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 10;
    int index = 0;
    int channel_num = 3;
    unsigned char data[nx * ny * channel_num];
    // std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *world = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus, 0.0, 1.0);

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
    stbi_write_png("chapter-14.png", nx, ny, channel_num, data, 0);
}