#pragma once

namespace renderer {


class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
    Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

};


}
