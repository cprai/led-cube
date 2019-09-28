#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "renderer/mesh.h"

namespace renderer {


class OBJReader {
public:
    OBJReader(std::ifstream& file, Mesh& mesh) : file(file), mesh(mesh) { parseFile(); }

private:
    std::ifstream& file;
    Mesh& mesh;

    enum LineType{
        VERTEX,
        FACE,
        IGNORE,
    };

    void parseFile() {
        for (std::string line; std::getline(file, line); ) {
            parseLine(line);
        }
    }

    LineType getLineType(const std::string& line) {
        if (line.length() == 0) {
            return LineType::IGNORE;
        }

        // Access is safe becase cheched length > 0
        if (line[0] == 'v') {
            return LineType::VERTEX;
        }

        if (line[0] == 'f') {
            return LineType::FACE;
        }

        return LineType::IGNORE;
    }

    void parseLine(const std::string& line) {
        switch (getLineType(line)) {
            case LineType::VERTEX:
                parseVertex(line);
                return;

            case LineType::FACE:
                parseFace(line);
                return;

            case LineType::IGNORE:
            default:
                return;
        }
    }

    inline std::vector<std::string> tokenizeOnWhitespace(const std::string& line) {
        std::istringstream tokenizer(line);
        std::vector<std::string> tokens;

        for (std::string token; tokenizer >> token; ) {
            tokens.push_back(token);
        }

        return tokens;
    }

    void parseVertex(const std::string& line) {
        std::vector<std::string> tokens = tokenizeOnWhitespace(line);

        // Invalid vertex? ignore
        if (!(tokens.size() == 4 || tokens.size() == 5)) {
            return;
        }

        // Ignore w component if it exists
        float x = std::stof(tokens[1]);
        float y = std::stof(tokens[2]);
        float z = std::stof(tokens[3]);

        mesh.vertices.push_back({x, y, z});
    }

    void parseFace(const std::string& line) {
        std::vector<std::string> tokens = tokenizeOnWhitespace(line);

        // Only want triangles
        if (tokens.size() != 4) {
            return;
        }

        // Face could also have texture coordinates and other stuff
        // But stoi will ignore everything after it hits the first '/'
        int v1 = std::stoi(tokens[1]);
        int v2 = std::stoi(tokens[2]);
        int v3 = std::stoi(tokens[3]);

        // Negative index means to start from the back of current face array
        // Fix to be proper index from start of array
        if (v1 < 0) v1 += mesh.vertices.size();
        if (v2 < 0) v2 += mesh.vertices.size();
        if (v3 < 0) v3 += mesh.vertices.size();

        mesh.triangles.push_back({v1, v2, v3});
    }

};


}
