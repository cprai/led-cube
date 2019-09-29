#pragma once

#include <cmath>
#include <cstring>

namespace renderer {

// Using 3D homogenous coordinates
class Transformation {
public:
    void transform(Vertex vertices[], int numberOfVertices) {
        for (int i = 0; i < numberOfVertices; i++) {
            float u1 = vertices[i].x;
            float u2 = vertices[i].y;
            float u3 = vertices[i].z;
            float u4 = 1.0f;

            float v1 = u1*mx[0][0] + u2*mx[0][1] + u3*mx[0][2] + u4*mx[0][3];
            float v2 = u1*mx[1][0] + u2*mx[1][1] + u3*mx[1][2] + u4*mx[1][3];
            float v3 = u1*mx[2][0] + u2*mx[2][1] + u3*mx[2][2] + u4*mx[2][3];
            float v4 = u1*mx[3][0] + u2*mx[3][1] + u3*mx[3][2] + u4*mx[3][3];

            vertices[i].x = v1/v4;
            vertices[i].y = v2/v4;
            vertices[i].z = v3/v4;
        }
    }

    Transformation rightMultiply(Transformation B) {
        Transformation C;

        for(int i = 0; i < 4; ++i) {
            C.mx[0][i] = B.mx[0][i]*mx[0][0] + B.mx[1][i]*mx[0][1] + B.mx[2][i]*mx[0][2] + B.mx[3][i]*mx[0][3];
            C.mx[1][i] = B.mx[0][i]*mx[1][0] + B.mx[1][i]*mx[1][1] + B.mx[2][i]*mx[1][2] + B.mx[3][i]*mx[1][3];
            C.mx[2][i] = B.mx[0][i]*mx[2][0] + B.mx[1][i]*mx[2][1] + B.mx[2][i]*mx[2][2] + B.mx[3][i]*mx[2][3];
            C.mx[3][i] = B.mx[0][i]*mx[3][0] + B.mx[1][i]*mx[3][1] + B.mx[2][i]*mx[3][2] + B.mx[3][i]*mx[3][3];
        }

        return C;
    }

    // copied code: http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
    Transformation inverse() {
        Transformation I;
        float m00 = mx[0][0];
        float m01 = mx[0][1];
        float m02 = mx[0][2];
        float m03 = mx[0][3];
        float m10 = mx[1][0];
        float m11 = mx[1][1];
        float m12 = mx[1][2];
        float m13 = mx[1][3];
        float m20 = mx[2][0];
        float m21 = mx[2][1];
        float m22 = mx[2][2];
        float m23 = mx[2][3];
        float m30 = mx[3][0];
        float m31 = mx[3][1];
        float m32 = mx[3][2];
        float m33 = mx[3][3];

        float determinant =
        m03*m12*m21*m30 - m02*m13*m21*m30 - m03*m11*m22*m30 + m01*m13*m22*m30+
        m02*m11*m23*m30 - m01*m12*m23*m30 - m03*m12*m20*m31 + m02*m13*m20*m31+
        m03*m10*m22*m31 - m00*m13*m22*m31 - m02*m10*m23*m31 + m00*m12*m23*m31+
        m03*m11*m20*m32 - m01*m13*m20*m32 - m03*m10*m21*m32 + m00*m13*m21*m32+
        m01*m10*m23*m32 - m00*m11*m23*m32 - m02*m11*m20*m33 + m01*m12*m20*m33+
        m02*m10*m21*m33 - m00*m12*m21*m33 - m01*m10*m22*m33 + m00*m11*m22*m33;

        I.mx[0][0] = (m12*m23*m31 - m13*m22*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 + m11*m22*m33)/determinant;
        I.mx[0][1] = (m03*m22*m31 - m02*m23*m31 - m03*m21*m32 + m01*m23*m32 + m02*m21*m33 - m01*m22*m33)/determinant;
        I.mx[0][2] = (m02*m13*m31 - m03*m12*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 + m01*m12*m33)/determinant;
        I.mx[0][3] = (m03*m12*m21 - m02*m13*m21 - m03*m11*m22 + m01*m13*m22 + m02*m11*m23 - m01*m12*m23)/determinant;
        I.mx[1][0] = (m13*m22*m30 - m12*m23*m30 - m13*m20*m32 + m10*m23*m32 + m12*m20*m33 - m10*m22*m33)/determinant;
        I.mx[1][1] = (m02*m23*m30 - m03*m22*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 + m00*m22*m33)/determinant;
        I.mx[1][2] = (m03*m12*m30 - m02*m13*m30 - m03*m10*m32 + m00*m13*m32 + m02*m10*m33 - m00*m12*m33)/determinant;
        I.mx[1][3] = (m02*m13*m20 - m03*m12*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 + m00*m12*m23)/determinant;
        I.mx[2][0] = (m11*m23*m30 - m13*m21*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 + m10*m21*m33)/determinant;
        I.mx[2][1] = (m03*m21*m30 - m01*m23*m30 - m03*m20*m31 + m00*m23*m31 + m01*m20*m33 - m00*m21*m33)/determinant;
        I.mx[2][2] = (m01*m13*m30 - m03*m11*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 + m00*m11*m33)/determinant;
        I.mx[2][3] = (m03*m11*m20 - m01*m13*m20 - m03*m10*m21 + m00*m13*m21 + m01*m10*m23 - m00*m11*m23)/determinant;
        I.mx[3][0] = (m12*m21*m30 - m11*m22*m30 - m12*m20*m31 + m10*m22*m31 + m11*m20*m32 - m10*m21*m32)/determinant;
        I.mx[3][1] = (m01*m22*m30 - m02*m21*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 + m00*m21*m32)/determinant;
        I.mx[3][2] = (m02*m11*m30 - m01*m12*m30 - m02*m10*m31 + m00*m12*m31 + m01*m10*m32 - m00*m11*m32)/determinant;
        I.mx[3][3] = (m01*m12*m20 - m02*m11*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 + m00*m11*m22)/determinant;

        return I;
    }

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
