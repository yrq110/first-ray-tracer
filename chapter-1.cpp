#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

int main()
{
    int nx = 200;
    int ny = 100;
    int index = 0;
    int channel_num = 3;
    unsigned char data[nx * ny * channel_num];
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            data[index++] = ir;
            data[index++] = ig;
            data[index++] = ib;
        }
    }
    stbi_write_png("test.png", nx, ny, channel_num, data, 0);
}
