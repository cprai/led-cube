#pragma once

#include <vector>

#include "geometry/vector3.h"
#include "renderer/mesh.h"
#include "renderer/interpolator.h"

namespace renderer {

class PointCloud {
public:
    PointCloud(Mesh& mesh) {
        for (std::size_t i = 0; i < mesh.triangles.size(); i++) {
            Vector3 v1 = mesh.vertices[mesh.triangles[i].v1];
            Vector3 v2 = mesh.vertices[mesh.triangles[i].v2];
            Vector3 v3 = mesh.vertices[mesh.triangles[i].v3];

            Interpolator v12(v1, v2, 0.25f);
            Interpolator v13(v1, v3, 0.25f);

            while (!v12.done() || !v13.done()) {
                Interpolator v12_13(v12.get(), v13.get(), 0.25f);

                while (!v12_13.done()) {
                    points.push_back(v12_13.get());
                    v12_13.step();
                }

                v12.step();
                v13.step();
            }
        }
    }

public:
    std::vector<Vector3> points;

};


}
