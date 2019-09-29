#pragma once

namespace displayer {


class Color {
public:
    float r;
    float g;
    float b;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
    Vector3(float r, float g, float b) : r(r), g(g), b(b) { }

};


}
