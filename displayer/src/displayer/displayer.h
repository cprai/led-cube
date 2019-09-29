#pragma once

#include <iostream>

namespace displayer {


class Displayer {
public:
    Displayer() { }

    void display() {
        std::cout << "Call to display module" << std::endl;
    }
};


}
