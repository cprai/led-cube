#pragma once

#include "displayer/color.h"

#include "geometry/transformation.h"
#include "geometry/vector3.h"
#include "renderer/pointCloud.h"

namespace renderer {

class Entity {
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    displayer::Color color;

    PointCloud& mesh;

    Entity(Vector3 position, Vector3 rotation, Vector3 scale, displayer::Color color, PointCloud& mesh)
    : position(position), rotation(rotation), scale(scale), color(color), mesh(mesh) { }

    Transformation getVertexTransformationMatrix() {
        return Transformation::identity()
            .rightMultiply(Transformation::translate(position.x, position.y, position.z))
            .rightMultiply(Transformation::scale(scale.x, scale.y, scale.z))
            .rightMultiply(Transformation::rotateZ(rotation.z))
            .rightMultiply(Transformation::rotateY(rotation.y))
            .rightMultiply(Transformation::rotateX(rotation.x))
        ;
    }
};


}
