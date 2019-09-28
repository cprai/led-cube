#pragma once

#include "geometry/vector3.h"
#include "renderer/mesh.h"

namespace renderer {

class Entity {
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Mesh& mesh;
};


}
