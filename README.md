# First Ray Tracer

Ray tracing practice code from a great series by Peter Shirley. The code is written by C++.

![](image/main.png)

## [Ray Tracing in One Weekend](https://github.com/RayTracing/InOneWeekend)
* Chapter 1: **Output an image** ([stb_image](https://github.com/nothings/stb/blob/master/stb_image.h))
* Chapter 2: **The vec3 class**
* Chapter 3: **Rays, a simple camera, and background**
* Chapter 4: **Adding a sphere**
* Chapter 5.1: **Surface normals**
* Chapter 5.2: **Multiple objects**
* Chapter 6: **Anti aliasing**
* Chapter 7: **Diffuse materials**
* Chapter 8: **Metal**
  * The article lacks description of changing at sphere.h and new random.h files.
* Chapter 9: **Dielectrics**
* Chapter 10: **Positionable camera**
* Chapter 11: **Defocus blur**

## [Ray Tracing: The Next Week](https://github.com/RayTracing/TheNextWeek)

* Chapter 12: **Motion blur** 
  * In page 4 code block: `albedo->value`, at this time haven't has the `texture` class yet.
* Chapter 13: **Bounding Volume Hierarchies**
* Chapter 14: **Solid textures**
* Chapter 15: **Perlin noise**
  * While calling noise_texture() function you should input scale parameter, but the article does not mention it.
* Chapter 16: **Image texture mapping**
  * Should set attunation with new `rec.u` and `rec.v` values in scatter function of lambertian material.
* Chapter 17.1: **Rectangles and lights**
  * Remember to increase `vfov` value of `Camera` to see all objects.
* Chapter 17.2: **Cornell box: walls**
* Chapter 18: **Instances - Cornell box: balls**
* Chapter 19: **Volumes**

## [Ray Tracing: The Rest of Your Life](https://github.com/RayTracing/TheRestOfYourLife)

* Chapter 20: **A Simple Monte Carlo Program**
* Chapter 21: **One Dimensional MC Integration**
* Chapter 22: **MC Integration on the Sphere Directions**
* Chapter 23: **Importance Sampling Materials**
