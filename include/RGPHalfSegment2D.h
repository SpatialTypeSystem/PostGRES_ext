#ifndef RGPHALFSEGMENT2D_H
#define RGPHALFSEGMENT2D_H

#include "RGPPoint2D.h"
#include "RGPSegment2D.h"

class RGPHalfSegment2D {
public:
  // Members

  RGPSegment2D segment;
  RGPPoint2D dominantPoint;
  bool isLeftFlag;
  Number m; // Slope

  // Constructors

  RGPHalfSegment2D(RGPSegment2D s, RGPPoint2D dp);
  ~RGPHalfSegment2D();

  // Methods

  bool operator==(const RGPHalfSegment2D &rhs);
  bool operator!=(const RGPHalfSegment2D &rhs);
  bool operator<(const RGPHalfSegment2D &rhs);
  bool operator<=(const RGPHalfSegment2D &rhs);
  bool operator>(const RGPHalfSegment2D &rhs);
  bool operator>=(const RGPHalfSegment2D &rhs);
  bool isLeft();
  Number sqLen() const; // Square of length
};

class RGPAnnotatedHalfSegment2D : public RGPHalfSegment2D {
public:
  // Members

  bool insideIsAbove;

  // Constructors

  RGPAnnotatedHalfSegment2D(RGPSegment2D s, RGPPoint2D dp, bool regAbove);
  ~RGPAnnotatedHalfSegment2D();

  // Methods
};

#endif // RGPHALFSEGMENT2D_H
