#include "../include/RGPHalfSegment2D.h"

// RGPHalfSegment2D
// Constructors

RGPHalfSegment2D::RGPHalfSegment2D(RGPSegment2D s, RGPPoint2D dp) : segment(s), dominantPoint(dp) {}
RGPHalfSegment2D::~RGPHalfSegment2D() {}


// RGPAnnotatedHalfSegment2D
// Constructors

RGPAnnotatedHalfSegment2D::RGPAnnotatedHalfSegment2D(RGPSegment2D s,
    RGPPoint2D dp, bool regAbove) : RGPHalfSegment2D::RGPHalfSegment2D(s, dp) {
    this->insideIsAbove = regAbove;
}

RGPAnnotatedHalfSegment2D::~RGPAnnotatedHalfSegment2D() {}
