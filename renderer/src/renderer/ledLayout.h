#pragma once

#include <map>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>

#include "geometry/vector3.h"

namespace renderer {

class LEDNode {
public:
    Vector3 position;
    int index;
    LEDNode* next;

    LEDNode(Vector3 position, int index, LEDNode* next) : position(position), index(index), next(next) { }

};

class LEDLayout {

using Bin = std::tuple<int, int, int>;
using LED = std::tuple<Vector3, int>;

public:
    LEDLayout(std::vector<Vector3> samplePoints, float binSize) : binSize(binSize) {
        std::map<Bin, std::vector<LED>> initialLayout;

        std::vector<int> xCoordinates;
        std::vector<int> yCoordinates;
        std::vector<int> zCoordinates;

        for (std::size_t index = 0; index < samplePoints.size(); index++) {
            Bin bin = getBin(samplePoints[index]);

            xCoordinates.push_back(std::get<0>(bin));
            yCoordinates.push_back(std::get<1>(bin));
            zCoordinates.push_back(std::get<2>(bin));

            // Will recieve a nullptr for initialLayout[bin] if did not exist
            initialLayout[bin].push_back({samplePoints[index], index});
        }

        // Add padding to min and max
        xMin = *std::min_element(xCoordinates.begin(), xCoordinates.end()) - 1;
        yMin = *std::min_element(yCoordinates.begin(), yCoordinates.end()) - 1;
        zMin = *std::min_element(zCoordinates.begin(), zCoordinates.end()) - 1;

        xMax = *std::max_element(xCoordinates.begin(), xCoordinates.end()) + 1;
        yMax = *std::max_element(yCoordinates.begin(), yCoordinates.end()) + 1;
        zMax = *std::max_element(zCoordinates.begin(), zCoordinates.end()) + 1;

        xRange = xMax - xMin;
        yRange = yMax - yMin;
        zRange = zMax - zMin;

        // Create array of null pointers
        layout = new LEDNode*[xRange*yRange*zRange]();

        for (auto const& [bin, leds] : initialLayout) {
            int x = std::get<0>(bin);
            int y = std::get<1>(bin);
            int z = std::get<2>(bin);

            for (auto const& [position, index] : leds) {

                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        for (int k = -1; k <= 1; k++) {
                            layout[getLayoutCoordinate(x + i, y + j, z + k)] = new LEDNode(position, index, layout[getLayoutCoordinate(x + i, y + j, z + k)]);
                        }
                    }
                }

            }
        }
    }

    LEDNode* getLEDs(Vector3 position) {
        int x = (int)std::floor(position.x/binSize);
        int y = (int)std::floor(position.y/binSize);
        int z = (int)std::floor(position.z/binSize);

        if (x < xMin || x >= xMax) return nullptr;
        if (y < yMin || y >= yMax) return nullptr;
        if (z < zMin || z >= zMax) return nullptr;

        return layout[getLayoutCoordinate(x, y, z)];
    }

private:
    float binSize;

    int xRange, xMin, xMax;
    int yRange, yMin, yMax;
    int zRange, zMin, zMax;

    LEDNode** layout;

    Bin getBin(Vector3 position) {
        int x = (int)std::floor(position.x/binSize);
        int y = (int)std::floor(position.y/binSize);
        int z = (int)std::floor(position.z/binSize);

        return {x, y, z};
    }

    inline int getLayoutCoordinate(int x, int y, int z) {
        return ( (z - zMin)*xRange*yRange ) + ( (y - yMin)*xRange ) + (x - xMin);
    }

};


}
