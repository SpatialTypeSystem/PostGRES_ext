#include "../include/RGPOperations2D.h"

/* Here we will use an orientation-based method of concluding whether two
 * segments intersect.
 */
bool RGPOperations2D::intersecting(RGPSegment2D s1, RGPSegment2D s2)
{
  Number s1o1 = orientation(s1.point1, s1.point2, s2.point1);
  Number s1o2 = orientation(s1.point1, s1.point2, s2.point2);
  Number s2o1 = orientation(s2.point1, s2.point2, s1.point1);
  Number s2o2 = orientation(s2.point1, s2.point2, s1.point2);

  return (s1o1 != s1o2) && (s2o1 != s2o2);
}

/* Returns either an optional RGPPoint2D that designates the intersection of
 * the two RGPSegment2D's. No intersection is represented by an empty optional.
 */
optional<RGPPoint2D> RGPOperations2D::intersectionOf(RGPSegment2D s1,
    RGPSegment2D s2)
{
  if (intersecting(s1, s2))
  {
    // Slope of s1
    Number m1 = (s1.point2.y - s1.point1.y) / (s1.point2.x - s1.point1.y);
    // Slope of s2
    Number m2 = (s2.point2.y - s2.point1.y) / (s2.point2.x - s2.point1.y);

    // x value of intersection
    Number x = ((m1 * s1.point1.x + s1.point1.y) - (m2 * s2.point1.x + s2
        .point1.y)) / (m1 - m2);
    // y value of intersection
    Number y = m1 * x - (m1 * s1.point1.x + s1.point1.y);

    return RGPPoint2D(x,y);
  }

  return {}; // Empty optional
}

/* Returns whether three points are in a clockwise, counter-clockwise or
 * co-linear orientation. This will depend on the order they are given in.
 * 0 -> Co-linear
 * 1 -> Clockwise
 * 2 -> Counter-clockwise
 */
Number RGPOperations2D::orientation(RGPPoint2D p1, RGPPoint2D p2, RGPPoint2D p3)
{
  Number n = ((p2.y - p1.y) * (p3.x - p2.x)) - ((p2.x - p1.x) * (p3.y - p2.y));

  if (n == 0)
  {
    return 0; // Co-linear
  }
  else if (n > 0)
  {
    return 1; // Clockwise
  }
  else
  {
    return 2; // Counter-clockwise
  }
}
