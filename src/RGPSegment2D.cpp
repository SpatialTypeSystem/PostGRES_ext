#include "../include/RGPSegment2D.h"

// Constructors

RGPSegment2D::RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2)
    : point1(p1 < p2 ? p1 : p2), point2(p1 < p2 ? p2 : p1) {}
RGPSegment2D::RGPSegment2D()
{
  RGPPoint2D p1(Number("0"), Number("0")), p2(Number("1"), Number("0"));
  point1 = p1 < p2 ? p1 : p2;
  point2 = p1 < p2 ? p2 : p1;
}
RGPSegment2D::RGPSegment2D(std::string segment)
{
  std::string s1, s2;
  int i, j, slength = segment.size();
  for (i = 0; segment[i] != ')'; i++)
    ;
  s1 = segment.substr(0, i + 1);
  for (j = i + 2; segment[j] != ')'; j++)
    ;
  s2 = segment.substr(i + 2, slength - i - 2);
  RGPPoint2D p1(s1), p2(s2);
  point1 = p1 < p2 ? p1 : p2;
  point2 = p1 < p2 ? p2 : p1;
}
RGPSegment2D::~RGPSegment2D() {}

// Methods

bool RGPSegment2D::operator==(const RGPSegment2D &rhs)
{
  if (point1 == rhs.point1 && point2 == rhs.point2)
    return true;
  else
    return false;
}
bool RGPSegment2D::operator!=(const RGPSegment2D &rhs)
{
  if (point1 == rhs.point1 && point2 == rhs.point2)
    return false;
  else
    return true;
}
bool RGPSegment2D::operator<(const RGPSegment2D &rhs)
{
  if (point1 < rhs.point1 && point2 < rhs.point1)
    return true;
  return false;
}
bool RGPSegment2D::operator<=(const RGPSegment2D &rhs)
{
  if ((*this) < rhs || (*this) == rhs)
    return true;
  return false;
}
bool RGPSegment2D::operator>(const RGPSegment2D &rhs)
{
  return !((*this) <= rhs);
}
bool RGPSegment2D::operator>=(const RGPSegment2D &rhs)
{
  return !((*this) < rhs);
}

bool RGPSegment2D::isPointAbove(const RGPPoint2D &p)
{
  Number s = (point2.y - point1.y) * p.x + (point1.x - point2.x) * p.y + (point2.x * point1.y - point1.x * point2.y);
  if (s > Number("0"))
  {
    return true;
  }
  return false;
}

bool RGPSegment2D::isPointBelow(const RGPPoint2D &p)
{
  Number s = (point2.y - point1.y) * p.x + (point1.x - point2.x) * p.y + (point2.x * point1.y - point1.x * point2.y);
  if (s < Number("0"))
  {
    return true;
  }
  return false;
}

bool RGPSegment2D::isPointOnSegment(const RGPPoint2D &p)
{
  Number s = (point2.y - point1.y) * p.x + (point1.x - point2.x) * p.y + (point2.x * point1.y - point1.x * point2.y);
  if (s == Number("0"))
  {
    return true;
  }
  return false;
}

bool RGPSegment2D::contains(const RGPPoint2D p)
{
  if (p.x <= std::max(point1.x, point2.x) &&
      p.x >= std::min(point1.x, point2.x) &&
      p.y <= std::max(point1.y, point2.y) &&
      p.y >= std::min(point1.y, point2.y))
  {
    return true;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const RGPSegment2D p)
{
  os << p.point1 << "," << p.point2;
  return os;
}

std::istream &operator>>(std::istream &is, RGPSegment2D &s)
{
  std::string input;
  getline(is, input);
  RGPSegment2D s1(input);
  s.point1 = s1.point1;
  s.point2 = s1.point2;
  return is;
}
