#include <iostream>

#include "geometry/vector3.h"
#include "displayer/displayer.h"

#define N 7

int main() {
    displayer::Displayer<N> displayer;

    renderer::Vector3 outputBuffer[N];
    int i = 0;
    while (1) {
        if (i > 10) {
            i = 0;
        }
        float r = i * 0.1;
        float g = 1;
        float b = 0;
        for (int i = 0; i < N; i += 2) {
            outputBuffer[i] = {r, g, b};
        }


        // float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[0] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[1] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[1] = {r, g, b}; 
        
        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);     

        // outputBuffer[2] = {r, g, b}; 
        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[3] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[4] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[4] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[5] = {r, g, b};

        // r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);        
        // g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        // outputBuffer[6] = {r, g, b};


        // std::cout << "Output buffer:" << std::endl;
        // for (int i = 0; i < N; i++) {
        //     std::cout << "{" << outputBuffer[i].x << "," << outputBuffer[i].y << "," << outputBuffer[i].z << "}" << std::endl;
        // }

        displayer.display((displayer::Color*)outputBuffer);
        ++i;
        // nanosleep((const struct timespec[]){{0, 500000L}}, NULL);
    }
}
