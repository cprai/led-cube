#pragma once

#include <map>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>

#include "geometry/vector3.h"

namespace renderer {

class LEDLayout {

using Bin = std::tuple<int, int, int>;
using LED = std::tuple<Vector3, int>;

public:
    LEDLayout(std::vector<Vector3> samplePoints, float binSize) : binSize(binSize) {
        for (int index = 0; index < samplePoints.size(); index++) {
            Vector3 position = samplePoints[index];
            for (auto bin : getLocalBins(position)) {
                layout[bin].push_back({position, index});
            }
        }
    }

    std::vector<LED> getLEDsInRange(Vector3 position) {
        return layout[getBin(position)];
    }

private:
    float binSize;
    std::map<Bin, std::vector<LED>> layout;

    Bin getBin(Vector3 position) {
        int x = (int)std::floor(position.x/binSize);
        int y = (int)std::floor(position.y/binSize);
        int z = (int)std::floor(position.z/binSize);

        return {x, y, z};
    }

    std::vector<Bin> getLocalBins(Vector3 position) {
        int x = (int)std::floor(position.x/binSize);
        int y = (int)std::floor(position.y/binSize);
        int z = (int)std::floor(position.z/binSize);

        std::vector<Bin> bins;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    bins.push_back({x + i, y + j, z + k});
                }
            }
        }

        return bins;
    }

};


}
