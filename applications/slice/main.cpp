#include "geometry/vector3.h"
#include "renderer/renderer.h"
#include "displayer/displayer.h"

#include <iostream>
#include <iomanip>
#include "external/bitmap/bitmap_image.hpp"

#define N 100

using namespace renderer;

int main() {
    renderer::Renderer renderer;
    displayer::Displayer displayer;
    displayer.display();
    //renderer::Entity& teapot = renderer.createEntity({0, 0, 0}, {1, 0, 0}, {4, 4, 1}, renderer.loadMesh("simple.obj"));
    renderer::Entity& teapot = renderer.createEntity({0, 0, 0}, {0, 0, 3.14}, {1, 1, 1}, renderer.loadMesh("resources/teapot.obj"));
    //teapot.position.x += 3;

    //Vector3 samplePoints[1] = {{2.5, 1, 0}};
    //Vector3 outputBuffer[1];
    //renderer.render<1>(samplePoints, outputBuffer);

    float radius = 20.0f;
    Vector3 samplePoints[N*N];
    Vector3 outputBuffer[N*N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            samplePoints[j*N + i] = Vector3(i/(float)N*radius - radius/2, j/(float)N*radius - radius/2, 0.0f);
        }
    }
    renderer.render<N*N>(samplePoints, outputBuffer);
    bitmap_image image(N, N);
    image.clear();
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            //std::cout << std::fixed << std::setprecision(1) << outputBuffer[j*N + i].x << " ";
            Vector3 color = outputBuffer[j*N + i];
            image.set_pixel(i, j, color.x*255, color.y*255, color.z*255);
        }
        //std::cout << std::endl;
    }
    image.save_image("test.bmp");
    (void)teapot;
}
