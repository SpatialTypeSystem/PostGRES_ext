#include "../include/RGPSegment2D.h"

// Constructors

RGPSegment2D::RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2) : point1(p1), point2(p2) {}
RGPSegment2D::~RGPSegment2D() {}

// Methods

bool RGPSegment2D::operator==(const RGPSegment2D &rhs) const {}
bool RGPSegment2D::operator!=(const RGPSegment2D &rhs) const {}
bool RGPSegment2D::operator<(const RGPSegment2D &rhs) const {}
bool RGPSegment2D::operator<=(const RGPSegment2D &rhs) const {}
bool RGPSegment2D::operator>(const RGPSegment2D &rhs) const {}
bool RGPSegment2D::operator>=(const RGPSegment2D &rhs) const {}

bool RGPSegment2D::operator<(const RGPHalfSegment2D &rhs) const {
  return true;
}
bool RGPSegment2D::operator>(const RGPHalfSegment2D &rhs) const {
  return true;
}

bool RGPSegment2D::operator<(const RGPAnnotatedHalfSegment2D &rhs) const {
  return true;
}
bool RGPSegment2D::operator>(const RGPAnnotatedHalfSegment2D &rhs) const {
  return true;
}

bool RGPSegment2D::operator<(const RGPPoint2D &rhs) const {
  return true;
}
bool RGPSegment2D::operator>(const RGPPoint2D &rhs) const {
  return true;
}
