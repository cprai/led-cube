#pragma once

#include <cstdio>
#include <cstdint>

namespace displayer {


class Color {
public:
    float r;
    float g;
    float b;

    Color() : r(0.0f), g(0.0f), b(0.0f) { }
    Color(float r, float g, float b) : r(r), g(g), b(b) { }

    uint32_t asU32() {
        uint32_t value = 0;
        value |= ((uint8_t)(r*255)) << 24;
        value |= ((uint8_t)(g*255)) << 16;
        value |= ((uint8_t)(b*255)) << 8;
        return value;
    }

};


}
