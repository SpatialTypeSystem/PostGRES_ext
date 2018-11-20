#include "../include/RGPOperations2D.h"

int RGPOperations2D::orientation(RGPPoint2D point1, RGPPoint2D point2,
                                 RGPPoint2D point3) {
  Number x = (point2.y - point1.y) * (point3.x - point2.x) -
             (point3.y - point2.y) * (point2.x - point1.x);
  Number zero("0");
  if (x == zero)
    return COLLINEAR;
  else if (x > zero)
    return CLOCKWISE;
  else
    return COUNTERCLOCKWISE;
}

RGPPoint2D RGPOperations2D::intersection(RGPSegment2D s1, RGPSegment2D s2) {
  Number x1 = s1.point1.x, y1 = s1.point1.y, x2 = s1.point2.x, y2 = s1.point2.y,
         x3 = s2.point1.x, y3 = s2.point1.y, x4 = s2.point2.x, y4 = s2.point2.y,
         resX, resY, denom;
  denom = (x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1);
  resX = ((x2 * y1 - x1 * y2) * (x4 - x3) - (x4 * y3 - x3 * y4) * (x2 - x1)) /
         denom;
  resY = ((x2 * y1 - x1 * y2) * (y4 - y3) - (x4 * y3 - x3 * y4) * (y2 - y1)) /
         denom;
  RGPPoint2D intersectPoint(resX, resY);
  return intersectPoint;
}

optional<RGPPoint2D> RGPOperations2D::intersectionOf(RGPSegment2D s1,
                                                     RGPSegment2D s2) {
  int orientation1 = orientation(s1.point1, s1.point2, s2.point1);
  int orientation2 = orientation(s1.point1, s1.point2, s2.point2);
  int orientation3 = orientation(s2.point1, s2.point2, s1.point1);
  int orientation4 = orientation(s2.point1, s2.point2, s1.point2);

  if ((orientation1 != orientation2 && orientation3 != orientation4) ||
      (orientation1 == COLLINEAR && s1.contains(s2.point1)) ||
      (orientation2 == COLLINEAR && s1.contains(s2.point2)) ||
      (orientation3 == COLLINEAR && s2.contains(s1.point1)) ||
      (orientation4 == COLLINEAR && s2.contains(s1.point2))) {
    return {intersection(s1, s2)};
  }

  return std::nullopt;
}
