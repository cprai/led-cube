#pragma once

#include <cstdint>
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

        uint32_t interfaceBuffer[LEDCount];
        
        for (int i = 0; i < LEDCount; i++) {
            interfaceBuffer[i] = outputBuffer[i].asU32();

            std::cout << std::hex << interfaceBuffer[i] << std::endl;
        }

        pru_module_update(pru_module, interfaceBuffer);
    }

private:
    pru_module_t* pru_module;

};


}
