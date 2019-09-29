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
        //std::cout << " {" << v1.x << "," << v1.y << "," << v1.z << "}";
        //std::cout << " {" << v2.x << "," << v2.y << "," << v2.z << "}";
        //std::cout << " {" << v3.x << "," << v3.y << "," << v3.z << "}";
        //std::cout << std::endl;

        Vector3 point = v1;
        Vector3 vx = (v2 - v1);
        Vector3 vy = (v3 - v1);
        Vector3 normal = Vector3::cross(vx, vy).normalized();

        //std::cout << "normal {" << normal.x << "," << normal.y << "," << normal.z << "}";
        //std::cout << " vx {" << vx.x << "," << vx.y << "," << vx.z << "}";
        //std::cout << " vy {" << vy.x << "," << vy.y << "," << vy.z << "}";
        //std::cout << std::endl;

        Matrix3D cob = Matrix3D::changeOfBasis(vx, vy, normal);

        for (int i = 0; i < SamplePointCount; i++) {
            Vector3& samplePoint = samplePoints[i];
            Vector3& outputColor = outputBuffer[i];

            Vector3 p = samplePoint - point;
            Vector3 np = cob.transform(p);
            
            //std::cout << "np {" << np.x << "," << np.y << "," << np.z << "}" << std::endl;

            float distance = std::abs(np.z);

            float range = 0.1f;
            if (distance > range) continue;

            if (np.x < -0.25) continue;
            if (np.y < -0.25) continue;

            if (np.x + np.y > 1.25) continue;

            //std::cout << "sp {" << samplePoint.x << "," << samplePoint.y << "} " << distance << std::endl;

            float close = 1.0f - distance/range;
            if (outputColor.x > close) continue;
            outputColor = {close, close, close};
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
