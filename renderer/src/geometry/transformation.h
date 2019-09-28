#pragma once

namespace renderer {

// Using 3D homogenous coordinates
class Transformation {
public:

    // Static factories for creating various transformation matrices
    static Transformation identity() {
        Transformation t;

        for (int i = 0; i < 4; i++) {
            t.mx[i][i] = 1;
        }

        return t;
    }

    static Transformation translate(float x, float y, float z) {
        Transformation t;

        for(int i = 0; i < 4; i++) {
            t.mx[i][i] = 1;
        }

        t.mx[0][3] = x;
        t.mx[1][3] = y;
        t.mx[2][3] = z;

        return t;
    }

    static Transformation scale(float x, float y, float z) {
        Transformation t;

        t.mx[0][0] = x;
        t.mx[1][1] = y;
        t.mx[2][2] = z;
        t.mx[3][3] = 1;

        return t;
    }

    static Transformation rotateX(float a) {
        Transformation t;

        t.mx[0][0] = 1;
        t.mx[3][3] = 1;
        t.mx[1][1] = std::cos(a);
        t.mx[2][2] = std::cos(a);
        t.mx[2][1] = std::sin(a);
        t.mx[1][2] = -std::sin(a);

        return t;
    }

    static Transformation rotateY(float a) {
        Transformation t;

        t.mx[1][1] = 1;
        t.mx[3][3] = 1;
        t.mx[0][0] = std::cos(a);
        t.mx[2][2] = std::cos(a);
        t.mx[0][2] = std::sin(a);
        t.mx[2][0] = -std::sin(a);

        return t;
    }

    static Transformation rotateZ(float a) {
        Transformation t;

        t.mx[2][2] = 1;
        t.mx[3][3] = 1;
        t.mx[0][0] = std::cos(a);
        t.mx[1][1] = std::cos(a);
        t.mx[1][0] = std::sin(a);
        t.mx[0][1] = -std::sin(a);

        return t;
    }

private:
    float mx[4][4];

    Transformation() {
        // ============================= dynamic sizeof???
        std::memset((void*)mx, 0, 4*4*sizeof(float));
    }

};


}
