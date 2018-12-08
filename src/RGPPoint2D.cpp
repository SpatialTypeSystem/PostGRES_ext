#include "../include/RGPPoint2D.h"

// Constructors

RGPPoint2D::RGPPoint2D(Number x, Number y) : x(x), y(y) {}
RGPPoint2D::RGPPoint2D() : x(Number("0")), y(Number("0")) {}
RGPPoint2D::RGPPoint2D(std::string point)
{
  int i, slength = point.size();
  std::string s1, s2;
  for (i = 1; point[i] != ','; i++)
    ;
  s1 = point.substr(1, i - 1);
  s2 = point.substr(i + 1, slength - i - 2);
  x = Number(s1);
  y = Number(s2);
}
RGPPoint2D::~RGPPoint2D() {}

// Methods

bool RGPPoint2D::operator==(const RGPPoint2D &rhs)
{
  if (x == rhs.x && y == rhs.y)
    return true;
  else
    return false;
}
bool RGPPoint2D::operator!=(const RGPPoint2D &rhs) { return !((*this) == rhs); }
bool RGPPoint2D::operator<(const RGPPoint2D &rhs)
{
  if (x < rhs.x || (x == rhs.x && y < rhs.y))
    return true;
  else
    return false;
}
bool RGPPoint2D::operator<=(const RGPPoint2D &rhs)
{
  return (*this) < rhs || (*this) == rhs;
}
bool RGPPoint2D::operator>(const RGPPoint2D &rhs) { return !((*this) <= rhs); }
bool RGPPoint2D::operator>=(const RGPPoint2D &rhs) { return !((*this) < rhs); }

std::ostream &operator<<(std::ostream &os, const RGPPoint2D p)
{
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

std::istream &operator>>(std::istream &is, RGPPoint2D &p)
{
  std::string input;
  getline(is, input);
  RGPPoint2D p1(input);
  p.x = p1.x;
  p.y = p1.y;
  return is;
}