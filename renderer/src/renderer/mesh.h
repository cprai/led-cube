#pragma once

#include <vector>

#include "geometry/vertex.h"
#include "geometry/triangle.h"

namespace renderer {

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;

};


}
