#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"
#include "base/vec3.h"

int main()
{
    int nx = 200;
    int ny = 100;
    int index = 0;
    int channel_num = 3;
    unsigned char data[nx * ny * channel_num];
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            data[index++] = ir;
            data[index++] = ig;
            data[index++] = ib;
        }
    }
    stbi_write_png("chapter-2.png", nx, ny, channel_num, data, 0);
}
