#pragma once

#include <cstring>

#include "geometry/vector3.h"

namespace renderer {

class Matrix3D {
public:
    Vector3 transform(Vector3 a) {
        float u1 = a.x;
        float u2 = a.y;
        float u3 = a.z;

        float v1 = u1*mx[0][0] + u2*mx[0][1] + u3*mx[0][2];
        float v2 = u1*mx[1][0] + u2*mx[1][1] + u3*mx[1][2];
        float v3 = u1*mx[2][0] + u2*mx[2][1] + u3*mx[2][2];

        return {v1, v2, v3};
    }

    static Matrix3D changeOfBasis(Vector3 a, Vector3 b, Vector3 c) {
        Matrix3D t;

        t.mx[0][0] = a.x;
        t.mx[1][0] = a.y;
        t.mx[2][0] = a.z;

        t.mx[0][1] = b.x;
        t.mx[1][1] = b.y;
        t.mx[2][1] = b.z;

        t.mx[0][2] = c.x;
        t.mx[1][2] = c.y;
        t.mx[2][2] = c.z;

        return t.inverse();
    }

private:
    float mx[3][3];

    Matrix3D() {
        // ============================= dynamic sizeof???
        std::memset((void*)mx, 0, 3*3*sizeof(float));
    }

    // copied code: http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/threeD/index.htm
    Matrix3D inverse() {
        Matrix3D I;
        float m00 = mx[0][0];
        float m01 = mx[0][1];
        float m02 = mx[0][2];
        float m10 = mx[1][0];
        float m11 = mx[1][1];
        float m12 = mx[1][2];
        float m20 = mx[2][0];
        float m21 = mx[2][1];
        float m22 = mx[2][2];

        float determinant = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20;

        I.mx[0][0] = (m11*m22 - m12*m21)/determinant;
        I.mx[0][1] = (m02*m21 - m01*m22)/determinant;
        I.mx[0][2] = (m01*m12 - m02*m11)/determinant;
        I.mx[1][0] = (m12*m20 - m10*m22)/determinant;
        I.mx[1][1] = (m00*m22 - m02*m20)/determinant;
        I.mx[1][2] = (m02*m10 - m00*m12)/determinant;
        I.mx[2][0] = (m10*m21 - m11*m20)/determinant;
        I.mx[2][1] = (m01*m20 - m00*m21)/determinant;
        I.mx[2][2] = (m00*m11 - m01*m10)/determinant;

        return I;
    }

};


}
