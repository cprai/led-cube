#pragma once

#include <iostream>

#include "displayer/color.h"
#include "interface/pru_module.h"

namespace displayer {


template<int LEDCount>
class Displayer {
public:
    Displayer() {
        pru_module = pru_module_new(LEDCount);
    }

    ~Displayer() {
        pru_module_shutdown(pru_module);
    }

    void display(Color outputBuffer[LEDCount]) {
        std::cout << "Call to display module" << std::endl;

        std::cout << "Recieved output buffer:" << std::endl;
        for (int i = 0; i < LEDCount; i++) {
            std::cout << "{" << outputBuffer[i].r << "," << outputBuffer[i].g << "," << outputBuffer[i].b << "}" << std::endl;
        }
    }

private:
    pru_module_t* pru_module;

};


}
