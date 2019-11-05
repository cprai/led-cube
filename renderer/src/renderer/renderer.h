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

#include <iostream>
namespace renderer {


class Renderer {
public:
    Mesh& loadMesh(const std::string& path) {
        // If mesh already loaded
        if (auto search = loadedMeshes.find(path); search != loadedMeshes.end()) {
            return *search->second;
        }

        // Create empty mesh
        Mesh& newMesh = meshes.emplace_back();

        // Load mesh data from file
        // =========================================== Error handle file not found??
        std::ifstream file(path, std::ios_base::in);
        OBJParser parser(file, newMesh);
        file.close();

        // Use substr() to get a copy of the path string
        loadedMeshes.insert(std::pair(path.substr(), &newMesh));

        return newMesh;
    }

    Entity& createEntity(Vector3 position, Vector3 rotation, Vector3 scale, Mesh& mesh) {
        return entities.emplace_back(position, rotation, scale, mesh);
    }

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
                    float rangeNear = 1.1;
                    float rangeFar = 1.5;

                    float brightness = 0;
                    if (distance <= rangeNear) {
                        brightness = 1;
                    }
                    else if (distance <= rangeFar) {
                        brightness = 1 - (distance - rangeNear)/(rangeFar - rangeNear);
                    }

                    if (outputBuffer[i].x < brightness) outputBuffer[i].x = brightness;
                    if (outputBuffer[i].y < brightness) outputBuffer[i].y = brightness;
                    if (outputBuffer[i].z < brightness) outputBuffer[i].z = brightness;
                }

                if (vlrprog == vlrdist) {
                    break;
                }
            }

            if (v13prog == v13dist && v23prog == v23dist) {
                break;
            }
        }
    }

    template<int SamplePointCount>
    void render(Vector3 samplePoints[SamplePointCount], Vector3 outputBuffer[SamplePointCount]) {
        for (auto entity : entities) {
            auto& vertices = entity.mesh.vertices;
            auto transformedVertices = std::make_unique<Vertex[]>(vertices.size());
            std::copy(vertices.begin(), vertices.end(), transformedVertices.get());
            entity.getVertexTransformationMatrix().transform(transformedVertices.get(), vertices.size());

            for (std::size_t i = 0; i < entity.mesh.triangles.size(); i++) {
                Vertex x1 = transformedVertices[entity.mesh.triangles[i].v1];
                Vertex x2 = transformedVertices[entity.mesh.triangles[i].v2];
                Vertex x3 = transformedVertices[entity.mesh.triangles[i].v3];

                Vector3 v1 = {x1.x,x1.y,x1.z};
                Vector3 v2 = {x2.x,x2.y,x2.z};
                Vector3 v3 = {x3.x,x3.y,x3.z};

                renderTriangle<SamplePointCount>(v1, v2, v3, samplePoints, outputBuffer);
            }
        }
    }

private:
    std::vector<Entity> entities;
    std::vector<Mesh> meshes;
    std::unordered_map<std::string, Mesh*> loadedMeshes;

};


}
