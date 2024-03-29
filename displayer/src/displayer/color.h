#pragma once

namespace displayer {


class Color {
public:
    float r;
    float g;
    float b;

    Color() : r(0.0f), g(0.0f), b(0.0f) { }
    Color(float r, float g, float b) : r(r), g(g), b(b) { }

    Color mix(Color other, float influence) {
        return {
            r*(1.0f - influence) + other.r*influence,
            g*(1.0f - influence) + other.g*influence,
            b*(1.0f - influence) + other.b*influence,
        };
    }

};


}
