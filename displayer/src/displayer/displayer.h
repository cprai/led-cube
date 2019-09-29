#pragma once

#include <iostream>

#include "displayer/color.h"

namespace displayer {


class Displayer {
public:
    Displayer() { }

    template<int LEDCount>
    void display(Color outputBuffer[LEDCount]) {
        std::cout << "Call to display module" << std::endl;

        std::cout << "Recieved output buffer:" << std::endl;
        for (int i = 0; i < LEDCount; i++) {
            std::cout << "{" << outputBuffer[i].r << "," << outputBuffer[i].g << "," << outputBuffer[i].b << "}" << std::endl;
        }
    }
};


}
