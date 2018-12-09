#include "../include/RGPPoint2D.h"

// Constructors

RGPPoint2D::RGPPoint2D(Number x, Number y) : x(x), y(y) {}
RGPPoint2D::~RGPPoint2D() {}

// Methods

bool RGPPoint2D::operator==(const RGPPoint2D &rhs) {
  if (x == rhs.x && y == rhs.y)
    return true;
  else
    return false;
}
bool RGPPoint2D::operator!=(const RGPPoint2D &rhs) { return !((*this) == rhs); }
bool RGPPoint2D::operator<(const RGPPoint2D &rhs) {
  if (x < rhs.x || (x == rhs.x && y < rhs.y))
    return true;
  else
    return false;
}
bool RGPPoint2D::operator<=(const RGPPoint2D &rhs) {
  return (*this) < rhs || (*this) == rhs;
}
bool RGPPoint2D::operator>(const RGPPoint2D &rhs) { return !((*this) <= rhs); }
bool RGPPoint2D::operator>=(const RGPPoint2D &rhs) { return !((*this) < rhs); }

std::ostream &operator<<(std::ostream &os, const RGPPoint2D p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

std::istream &operator>>(std::istream &is, RGPPoint2D p) {
  // TODO: Check for invalid conditions
  char c;
  is >> c;
  is >> p.x;
  is >> c;
  is >> p.y;
  is >> c;
  return is;
}