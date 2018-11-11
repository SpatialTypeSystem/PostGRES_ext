/* This is a universal header for all Robust Geometric Primitives. Users
 * looking only for specific aspects of the RGP implementation should include
 * headers for those instead.
 */

#ifndef RGPOPERATIONS2D_H
#define RGPOPERATIONS2D_H

#include "RGPPoint2D.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"

class RGPOperations2D
{
public:
    static optional <RGPPoint2D> intersectionOf(RGPSegment2D s1,
        RGPSegment2D s2);
};

#endif //RGPOPERATIONS2D_H
