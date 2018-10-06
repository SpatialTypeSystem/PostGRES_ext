#include "../include/RGPHalfSegment2D.h"

// RGPHalfSegment2D
// Constructors

RGPHalfSegment2D::RGPHalfSegment2D() {}
RGPHalfSegment2D::RGPHalfSegment2D(RGPSegment2D s, RGPPoint2D dp) {}
RGPHalfSegment2D::~RGPHalfSegment2D() {}


// RGPAnnotatedHalfSegment2D
// Constructors

RGPAnnotatedHalfSegment2D::RGPAnnotatedHalfSegment2D(RGPSegment2D s, RGPPoint2D dp, bool regAbove) {
    this->insideIsAbove = regAbove;
}

RGPAnnotatedHalfSegment2D::~RGPAnnotatedHalfSegment2D() {}
