#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "file/objParser.h"
#include "file/mapParser.h"
#include "geometry/vector3.h"
#include "renderer/entity.h"
#include "renderer/mesh.h"
#include "renderer/pointCloud.h"
#include "renderer/ledLayout.h"

namespace renderer {


class Renderer {
public:
    Renderer(const std::string& samplePointsPath, float rangeNear, float rangeFar) :
        ledLayout({loadMap(samplePointsPath), 0.3f}),
        rangeNearSquared(rangeNear*rangeNear),
        rangeFarSquared(rangeFar*rangeFar)
    { }

    std::vector<Vector3> loadMap(const std::string& path) {
        std::vector<Vector3> samplePoints;

        std::ifstream file(path, std::ios_base::in);
        MAPParser parser(file, samplePoints);
        file.close();

        return samplePoints;
    }

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

    float ledDistanceToBrightnessFunction(float distanceSquared) {
        float brightness = 0;

        if (distanceSquared <= rangeNearSquared) {
            brightness = 1;
        }
        else if (distanceSquared <= rangeFarSquared) {
            brightness = 1 - (distanceSquared - rangeNearSquared)/(rangeFarSquared - rangeNearSquared);
        }

        return brightness;
    }

    template<int SamplePointCount>
    void render(Vector3 outputBuffer[SamplePointCount]) {
        for (auto entity : entities) {
            // Make buffer with same size as point cloud
            auto& points = entity.mesh.points;
            std::vector<Vector3> transformedPoints(points.size());

            // Transform local point coordinates into world space
            entity.getVertexTransformationMatrix().transform(points.get(), transformedPoints.get(), points.size());

            for (auto surfacePoint : transformedPoints) {
                for (auto [ledPosition, ledIndex] : ledLayout.getLEDsInRange(surfacePoint)) {
                    float distanceSquared = (ledPosition - surfacePoint).squaredMagnitude();
                    float brightness = ledDistanceToBrightnessFunction(distanceSquared);

                    if (outputBuffer[ledIndex].x < brightness) outputBuffer[ledIndex].x = brightness;
                    if (outputBuffer[ledIndex].y < brightness) outputBuffer[ledIndex].y = brightness;
                    if (outputBuffer[ledIndex].z < brightness) outputBuffer[ledIndex].z = brightness;
                }
            }
        }
    }

private:
    LEDLayout ledLayout;
    std::vector<Entity> entities;
    std::vector<PointCloud> meshes;
    std::unordered_map<std::string, PointCloud*> loadedMeshes;

    float rangeNearSquared, rangeFarSquared;

};


}
