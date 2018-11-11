#ifndef RGPHALFSEGMENT2D_H
#define RGPHALFSEGMENT2D_H

#include "RGPPoint2D.h"
#include "RGPSegment2D.h"

class RGPHalfSegment2D
{
public:

    // Members

    RGPSegment2D segment;
    RGPPoint2D dominantPoint;

    // Constructors

    RGPHalfSegment2D(RGPSegment2D s, RGPPoint2D dp);
    ~RGPHalfSegment2D();

    // Methods

    bool operator==(const RGPHalfSegment2D &rhs) const;
    bool operator!=(const RGPHalfSegment2D &rhs) const;
    bool operator<(const RGPHalfSegment2D &rhs) const;
    bool operator<=(const RGPHalfSegment2D &rhs) const;
    bool operator>(const RGPHalfSegment2D &rhs) const;
    bool operator>=(const RGPHalfSegment2D &rhs) const;

};

class RGPAnnotatedHalfSegment2D : public RGPHalfSegment2D
{
public:

    // Members

    bool insideIsAbove;

    // Constructors

    RGPAnnotatedHalfSegment2D(RGPSegment2D s, RGPPoint2D dp, bool regAbove);
    ~RGPAnnotatedHalfSegment2D();

    // Methods

};

#endif //RGPHALFSEGMENT2D_H
