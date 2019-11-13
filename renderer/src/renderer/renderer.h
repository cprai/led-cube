#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "displayer/color.h"

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

    Entity& createEntity(Vector3 position, Vector3 rotation, Vector3 scale, displayer::Color color, PointCloud& mesh) {
        return entities.emplace_back(position, rotation, scale, color, mesh);
    }

<<<<<<< HEAD
    template<int SamplePointCount>
    void renderTriangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 samplePoints[SamplePointCount], Vector3 outputBuffer[SamplePointCount]) {
        // ============================================ Error deal with degenerate triangles
        float v13dist = (v3 - v1).magnitude();
        float v23dist = (v3 - v2).magnitude();
        float v13prog = 0;
        float v23prog = 0;
        Vector3 v13step = (v3 - v1).normalized()*0.25;
        Vector3 v23step = (v3 - v2).normalized()*0.25;
        for (Vector3 v13ptr = v1, v23ptr = v2; ; v13ptr = v13ptr + v13step, v23ptr = v23ptr + v23step, v13prog += 0.25, v23prog += 0.25) {
            if (v13prog > v13dist) {
                v13ptr = v3;
                v13prog = v13dist;
            }
            if (v23prog > v23dist) {
                v23ptr = v3;
                v23prog = v23dist;
            }

            float vlrdist = (v23ptr - v13ptr).magnitude();
            float vlrprog = 0;
            Vector3 vlrstep = (v23ptr - v13ptr).normalized()*0.25;
            for (Vector3 vlrptr = v13ptr; ; vlrptr = vlrptr + vlrstep, vlrprog += 0.25) {
                if (vlrprog > vlrdist) {
                    vlrptr = v23ptr;
                    vlrprog = vlrdist;
                }

                for (int i = 0; i < SamplePointCount; i++) {
                    float distance = (samplePoints[i] - vlrptr).magnitude();

                    // brightness = 1 if distance < rangeNear
                    // brightness = [0, 1] if distance < rangeFar
                    float rangeNear = 0.1;
                    float rangeFar = 0.5;

                    float brightness = 0;
                    if (distance <= rangeNear) {
                        brightness = 1;
                    }
                    else if (distance <= rangeFar) {
                        brightness = 1 - (distance - rangeNear)/(rangeFar - rangeNear);
                    }

                    if (outputBuffer[i].x < brightness) outputBuffer[i].x = brightness;
                    if (outputBuffer[i].y < brightness) outputBuffer[i].y = 0;
                    if (outputBuffer[i].z < brightness) outputBuffer[i].z = 0;
                }

                if (vlrprog == vlrdist) {
                    break;
                }
            }

            if (v13prog == v13dist && v23prog == v23dist) {
                break;
            }
=======
    float ledDistanceToBrightnessFunction(float distanceSquared) {
        float brightness = 0;

        if (distanceSquared <= rangeNearSquared) {
            brightness = 1;
>>>>>>> master
        }
        else if (distanceSquared <= rangeFarSquared) {
            brightness = 1 - (distanceSquared - rangeNearSquared)/(rangeFarSquared - rangeNearSquared);
        }

        return brightness;
    }

    template<int SamplePointCount>
    void render(displayer::Color outputBuffer[SamplePointCount]) {
        for (auto entity : entities) {
            auto& points = entity.mesh.points;

            // Make buffer with same size as point cloud
            std::vector<Vector3> transformedPoints(points.size());

            // Transform local point coordinates into world space
            entity.getVertexTransformationMatrix().transform(points.data(), transformedPoints.data(), points.size());

            for (auto surfacePoint : transformedPoints) {
                for (auto [ledPosition, ledIndex] : ledLayout.getLEDsInRange(surfacePoint)) {
                    float distanceSquared = (ledPosition - surfacePoint).squaredMagnitude();
                    float brightness = ledDistanceToBrightnessFunction(distanceSquared);
                    outputBuffer[ledIndex] = outputBuffer[ledIndex].mix(entity.color, brightness);
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
