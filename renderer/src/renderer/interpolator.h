#pragma once

#include "geometry/vector3.h"

namespace renderer {

class Interpolator {
public:
    Interpolator(Vector3 begin, Vector3 end, float stepSize) :
        currentVector(begin),
        endVector(end),
        remainingSteps( (int)std::ceil( (end - begin).magnitude()/stepSize ) ),
        stepVector( (end - begin).normalized()*stepSize )
    { }

    Vector3 get() {
        return currentVector;
    }

    void step() {
        if (remainingSteps == 0) {
            return;
        }
        else if (remainingSteps == 1) {
            currentVector = endVector;
        }
        else {
            currentVector = currentVector + stepVector;
            remainingSteps--;
        }
    }

    bool done() {
        return remainingSteps == 0;
    }

private:
    Vector3 currentVector;
    Vector3 endVector;
    int remainingSteps;
    Vector3 stepVector;

};


}
