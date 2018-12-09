#include "../include/RGPSegment2D.h"

// Constructors

RGPSegment2D::RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2)
    : point1(p1 < p2 ? p1 : p2), point2(p1 < p2 ? p2 : p1) {}
RGPSegment2D::~RGPSegment2D() {}

// Methods

bool RGPSegment2D::operator==(const RGPSegment2D &rhs) {
  if (point1 == rhs.point1 && point2 == rhs.point2)
    return true;
  else
    return false;
}
bool RGPSegment2D::operator!=(const RGPSegment2D &rhs) {
  if (point1 == rhs.point1 && point2 == rhs.point2)
    return false;
  else
    return true;
}
bool RGPSegment2D::operator<(const RGPSegment2D &rhs) {
  if (point1 < rhs.point1 && point2 < rhs.point1)
    return true;
  return false;
}
bool RGPSegment2D::operator<=(const RGPSegment2D &rhs) {
  if ((*this) < rhs || (*this) == rhs)
    return true;
  return false;
}
bool RGPSegment2D::operator>(const RGPSegment2D &rhs) {
  return !((*this) <= rhs);
}
bool RGPSegment2D::operator>=(const RGPSegment2D &rhs) {
  return !((*this) < rhs);
}

bool RGPSegment2D::contains(const RGPPoint2D p) {
  if (p.x <= std::max(point1.x, point2.x) &&
      p.x >= std::min(point1.x, point2.x) &&
      p.y <= std::max(point1.y, point2.y) &&
      p.y >= std::min(point1.y, point2.y)) {
    return true;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const RGPSegment2D p) {
  os << p.point1 << "," << p.point2;
  return os;
}

std::istream &operator>>(std::istream &is, const RGPSegment2D p) {
  // TODO: Check for invalid conditions
  char c;
  is >> p.point1 >> c >> p.point2;
  return is;
}
