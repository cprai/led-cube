#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "geometry/vector3.h"

namespace renderer {


class MAPParser {
public:
    MAPParser(std::ifstream& file, std::vector<Vector3>& samplePoints) : file(file), samplePoints(samplePoints) { parseFile(); }

private:
    std::ifstream& file;
    std::vector<Vector3>& samplePoints;

    void parseFile() {
        for (std::string line; std::getline(file, line); ) {
            parseLine(line);
        }
    }

    void parseLine(const std::string& line) {
        std::vector<std::string> tokens = tokenizeOnWhitespace(line);

        float x = std::stof(tokens[0]);
        float y = std::stof(tokens[1]);
        float z = std::stof(tokens[2]);

        samplePoints.push_back({x, y, z});
    }

    inline std::vector<std::string> tokenizeOnWhitespace(const std::string& line) {
        std::istringstream tokenizer(line);
        std::vector<std::string> tokens;

        for (std::string token; tokenizer >> token; ) {
            tokens.push_back(token);
        }

        return tokens;
    }

};


}
