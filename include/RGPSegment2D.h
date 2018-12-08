/* RGPSegment2D is a robust geometric primitive representation of a segment
 * for a spatial database system.
 */

#ifndef RGPSEGMENT2D_H
#define RGPSEGMENT2D_H

#include "RGPPoint2D.h"

class RGPSegment2D {
public:
  // Members

  RGPPoint2D point1, point2;

  // Constructors

  RGPSegment2D(RGPPoint2D p1, RGPPoint2D p2);
  ~RGPSegment2D();

  // Methods

  bool operator==(const RGPSegment2D &rhs);
  bool operator!=(const RGPSegment2D &rhs);
  bool operator<(const RGPSegment2D &rhs);
  bool operator<=(const RGPSegment2D &rhs);
  bool operator>(const RGPSegment2D &rhs);
  bool operator>=(const RGPSegment2D &rhs);
  bool contains(const RGPPoint2D p);

  // Allows ouptut of an RGPSegment2D in the format of "(x1,y1),(x2,y2)"
  friend std::ostream &operator<<(std::ostream &os, const RGPSegment2D p);

  // Allows input of an RGPSegment2D in the format of "(x1,y1),(x2,y2)"
  // where ',' will be the delimiter between the x and y values of point1
  // and point2
  friend std::istream &operator>>(std::istream &is, const RGPSegment2D p);
};

#endif // RGPSEGMENT2D_H
