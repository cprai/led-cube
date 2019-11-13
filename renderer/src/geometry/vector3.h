#pragma once

#include <cmath>

namespace renderer {


class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
    Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

    Vector3 operator+(Vector3 other) {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(Vector3 other) {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator*(float scalar) {
        return {x*scalar, y*scalar, z*scalar};
    }

    Vector3 normalized() {
        float mag = magnitude();
        return {x/mag, y/mag, z/mag};
    }

    float squaredMagnitude() {
        return x*x + y*y + z*z;
    }

    float magnitude() {
        return std::sqrt(squaredMagnitude());
    }

    static float dot(Vector3 a, Vector3 b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    static Vector3 cross(Vector3 a, Vector3 b) {
        return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
    }

};


}
