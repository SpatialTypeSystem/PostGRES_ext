#ifndef RGPSEGMENT2D_H
#define RGPSEGMENT2D_H

#include "RGPPoint2D.h"

struct RGPSegment2D {

    // Members

    RGPPoint2D point1, point2;

    // Constructors
    
    RGPSegment2D();
    RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2);
    ~RGPSegment2D();

    // Methods

    bool operator==(const RGPSegment2D &rhs);
    bool operator!=(const RGPSegment2D &rhs);
    bool operator<(const RGPSegment2D &rhs);
    bool operator<=(const RGPSegment2D &rhs);
    bool operator>(const RGPSegment2D &rhs);
    bool operator>=(const RGPSegment2D &rhs);

};

#endif //RGPSEGMENT2D_H
