#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "geometry/vector3.h"
#include "file/objParser.h"
#include "renderer/entity.h"
#include "renderer/mesh.h"

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

private:
    std::vector<Entity> entities;
    std::vector<Mesh> meshes;
    std::unordered_map<std::string, Mesh*> loadedMeshes;

};


}
