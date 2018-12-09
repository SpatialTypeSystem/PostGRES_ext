/* RGPPoint2D is a robust geometric primitive representation of a point for a
 * spatial database system.
 */

#ifndef RGPPOINT2D_H
#define RGPPOINT2D_H

#include "Number.h"

class RGPPoint2D {
public:
  // Members

  Number x, y;

  // Constructors

  RGPPoint2D(Number x, Number y);
  ~RGPPoint2D();

  // Methods

  bool operator==(const RGPPoint2D &rhs);
  bool operator!=(const RGPPoint2D &rhs);
  bool operator<(const RGPPoint2D &rhs);
  bool operator<=(const RGPPoint2D &rhs);
  bool operator>(const RGPPoint2D &rhs);
  bool operator>=(const RGPPoint2D &rhs);

  // Allows ouptut of an RGPPoint2D in the format of "(x,y)"
  friend std::ostream &operator<<(std::ostream &os, const RGPPoint2D p);

  // Allows input of an RGPPoint2D in the format of "(x,y)" where ',' will be
  // the delimiter between the x and y values
  friend std::istream &operator>>(std::istream &is, RGPPoint2D p);
};

#endif // RGPPOINT2D_H
