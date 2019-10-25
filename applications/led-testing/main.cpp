#include <iostream>

#include "geometry/vector3.h"
#include "displayer/displayer.h"

#define N 5

int main() {
    displayer::Displayer<N> displayer;

    renderer::Vector3 outputBuffer[N];
    for (int i = 0; i < N; i += 2) {
        outputBuffer[i] = {1.0f, 0.0f, 0.0f};
    }

    std::cout << "Output buffer:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "{" << outputBuffer[i].x << "," << outputBuffer[i].y << "," << outputBuffer[i].z << "}" << std::endl;
    }

    displayer.display((displayer::Color*)outputBuffer);
}
