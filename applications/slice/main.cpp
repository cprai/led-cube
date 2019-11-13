#include "geometry/vector3.h"
#include "renderer/renderer.h"

#include <iostream>
#include <iomanip>
#include "external/bitmap/bitmap_image.hpp"

#define N 100

using namespace renderer;

int main() {
    /*
    // For generating map files
    float radius = 20.0f;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Vector3 a = Vector3(i/(float)N*radius - radius/2, j/(float)N*radius - radius/2, 0.0f);
            printf("%f %f %f\n", a.x, a.y, a.z);
        }
    }
    */

    renderer::Renderer renderer("resources/cube-100x100.map", 0.1, 0.5);
    renderer::Entity& teapot = renderer.createEntity({0, 0, 0}, {0, 0, 3.14}, {1, 1, 1}, {1, 0, 0}, renderer.loadMesh("resources/teapot.obj"));
    renderer::Entity& teapot2 = renderer.createEntity({0, 1, 0}, {0, 0, 3.14}, {1, 1, 1}, {0, 1, 1}, renderer.loadMesh("resources/teapot.obj"));

    displayer::Color outputBuffer[N*N];

    for (int i = 0; i < 10; i++) {
        renderer.render<N*N>(outputBuffer);
        printf("frame\n");
    }

    bitmap_image image(N, N);
    image.clear();
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            displayer::Color color = outputBuffer[j*N + i];
            image.set_pixel(i, j, color.r*255, color.g*255, color.b*255);
        }
    }

    image.save_image("test.bmp");
}
