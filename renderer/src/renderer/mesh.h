#pragma once

#include <vector>

#include "geometry/triangle.h"
#include "geometry/vector3.h"

namespace renderer {

class Mesh {
public:
    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;

};


}
