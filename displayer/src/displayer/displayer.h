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
    }
};


}
