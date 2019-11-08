#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "geometry/matrix3D.h"
#include "geometry/vector3.h"
#include "file/objParser.h"
#include "renderer/entity.h"
#include "renderer/mesh.h"
#include "renderer/pointCloud.h"

namespace renderer {


class Renderer {
public:
    PointCloud& loadMesh(const std::string& path) {
        // If mesh already loaded
        if (auto search = loadedMeshes.find(path); search != loadedMeshes.end()) {
            return *search->second;
        }

        // Create empty mesh
        Mesh parseResults;

        // Load mesh data from file
        // =========================================== Error handle file not found??
        std::ifstream file(path, std::ios_base::in);
        OBJParser parser(file, parseResults);
        file.close();

        // Create point cloud from mesh data
        PointCloud& newMesh = meshes.emplace_back(parseResults);

        // Store parsed result in map
        // Use substr() to get a copy of the path string
        loadedMeshes.insert(std::pair(path.substr(), &newMesh));

        return newMesh;
    }

    Entity& createEntity(Vector3 position, Vector3 rotation, Vector3 scale, PointCloud& mesh) {
        return entities.emplace_back(position, rotation, scale, mesh);
    }

    template<int SamplePointCount>
    void render(Vector3 samplePoints[SamplePointCount], Vector3 outputBuffer[SamplePointCount]) {
        for (auto entity : entities) {
            // Make copy of point cloud
            auto& points = entity.mesh.points;
            int numPoints = (int)points.size();
            auto transformedPoints = std::make_unique<Vector3[]>(points.size());
            std::copy(points.begin(), points.end(), transformedPoints.get());

            // Transform local point coordinates into world space
            entity.getVertexTransformationMatrix().transform(transformedPoints.get(), numPoints);

            for (int i = 0; i < numPoints; i++) {
                for (int j = 0; j < SamplePointCount; j++) {
                    float distance = (samplePoints[j] - transformedPoints[i]).magnitude();

                    float rangeNear = 0.1;
                    float rangeFar = 0.5;

                    float brightness = 0;
                    if (distance <= rangeNear) {
                        brightness = 1;
                    }
                    else if (distance <= rangeFar) {
                        brightness = 1 - (distance - rangeNear)/(rangeFar - rangeNear);
                    }

                    if (outputBuffer[j].x < brightness) outputBuffer[j].x = brightness;
                    if (outputBuffer[j].y < brightness) outputBuffer[j].y = brightness;
                    if (outputBuffer[j].z < brightness) outputBuffer[j].z = brightness;
                }
            }
        }
    }

private:
    std::vector<Entity> entities;
    std::vector<PointCloud> meshes;
    std::unordered_map<std::string, PointCloud*> loadedMeshes;

};


}
