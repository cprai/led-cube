#include "geometry/vector3.h"
#include "renderer/renderer.h"
#include "displayer/color.h"
#include "displayer/displayer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define N 49

std::vector<renderer::Vector3> samplePoints;

inline std::vector<std::string> tokenizeOnWhitespace(const std::string& line) {
    std::istringstream tokenizer(line);
    std::vector<std::string> tokens;

    for (std::string token; tokenizer >> token; ) {
        tokens.push_back(token);
    }

    return tokens;
}

void parseLine(const std::string& line) {
    std::vector<std::string> tokens = tokenizeOnWhitespace(line);

    float x = std::stof(tokens[0]);
    float y = std::stof(tokens[1]);
    float z = std::stof(tokens[2]);

    samplePoints.push_back({x, y, z});
}

int main() {
    std::ifstream file("resources/cube.map");

    for (std::string line; std::getline(file, line); ) {
        parseLine(line);
    }

    renderer::Renderer renderer;
    displayer::Displayer<N> displayer;

    // Arguments are {position}, {rotation}, {scale}
    renderer::Entity& teapot = renderer.createEntity({0, 0, 0}, {0, 0, 0}, {1, 1, 1}, renderer.loadMesh("resources/teapot.obj"));
    // To modify after creation:
    //teapot.scale.y = 15;

    renderer::Vector3 outputBuffer[N];
    renderer.render<N>(samplePoints.data(), outputBuffer);

    displayer.display((displayer::Color*)outputBuffer);
}
