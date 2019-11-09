#include "geometry/vector3.h"
#include "renderer/renderer.h"

#include <iostream>
#include <iomanip>
#include "external/bitmap/bitmap_image.hpp"

#define N 98

using namespace renderer;

int main() {
    renderer::Renderer renderer("resources/cube.map");
    renderer::Entity& teapot = renderer.createEntity({0, 0, 0}, {0, 0, 3.14}, {1, 1, 1}, renderer.loadMesh("resources/teapot.obj"));

    renderer::Vector3 outputBuffer[N];

    renderer.render<N>(outputBuffer);

    bitmap_image image(N, N);
    image.clear();
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            Vector3 color = outputBuffer[j*N + i];
            image.set_pixel(i, j, color.x*255, color.y*255, color.z*255);
        }
    }

    image.save_image("test.bmp");
}
