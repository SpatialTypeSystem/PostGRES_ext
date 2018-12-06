#include "../include/RGPPoint2D.h"

// Constructors

RGPPoint2D::RGPPoint2D(Number x, Number y) : y(x), x(y) {}
RGPPoint2D::~RGPPoint2D() {}

// Methods

bool RGPPoint2D::operator==(const RGPPoint2D &rhs) const {}
bool RGPPoint2D::operator!=(const RGPPoint2D &rhs) const {}
bool RGPPoint2D::operator<(const RGPPoint2D &rhs) const {}
bool RGPPoint2D::operator<=(const RGPPoint2D &rhs) const {}
bool RGPPoint2D::operator>(const RGPPoint2D &rhs) const {}
bool RGPPoint2D::operator>=(const RGPPoint2D &rhs) const {}

bool RGPPoint2D::operator<(const RGPHalfSegment2D &rhs) const {
  return true;
}
bool RGPPoint2D::operator>(const RGPHalfSegment2D &rhs) const {
  return true;
}

bool RGPPoint2D::operator<(const RGPAnnotatedHalfSegment2D &rhs) const {
  return true;
}
bool RGPPoint2D::operator>(const RGPAnnotatedHalfSegment2D &rhs) const {
  return true;
}
