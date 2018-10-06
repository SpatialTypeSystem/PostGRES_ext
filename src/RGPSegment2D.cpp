#include "../include/RGPSegment2D.h"

// Constructors

RGPSegment2D::RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2) : point1(RGPPoint2D(p1)), point2(RGPPoint2D(p2)) {}
RGPSegment2D::~RGPSegment2D() {}

// Methods

bool RGPSegment2D::operator==(const RGPSegment2D &rhs) {}
bool RGPSegment2D::operator!=(const RGPSegment2D &rhs) {}
bool RGPSegment2D::operator<(const RGPSegment2D &rhs) {}
bool RGPSegment2D::operator<=(const RGPSegment2D &rhs) {}
bool RGPSegment2D::operator>(const RGPSegment2D &rhs) {}
bool RGPSegment2D::operator>=(const RGPSegment2D &rhs) {}
