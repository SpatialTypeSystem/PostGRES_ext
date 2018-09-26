#ifndef RGPOPERATIONS_H
#define RGPOPERATIONS_H

#include "RGPPoint2D.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"
#include <optional>

struct RGPOperations {

    static optional<RGPPoint2D> intersectionOf(RGPSegment2D s1, RGPSegment2D s2);

};

#endif //RGPOPERATIONS_H
