#include "../include/RGPHalfSegment2D.h"

// RGPHalfSegment2D
// Constructors

RGPHalfSegment2D::RGPHalfSegment2D(RGPSegment2D s, RGPPoint2D dp)
    : segment(s), dominantPoint(dp) {
  if (dp == s.point1)
    isLeftFlag = true;
  else
    isLeftFlag = false;
	if(s.point2.x - s.point2.x != Number("0")) {
	  m = (s.point2.y - s.point1.y) / (s.point2.x - s.point2.x);
	} else {
		m = s.point2.x - s.point2.x;
	}
}
RGPHalfSegment2D::~RGPHalfSegment2D() {}

bool RGPHalfSegment2D::operator==(const RGPHalfSegment2D &rhs) {
  if (segment == rhs.segment && dominantPoint == rhs.dominantPoint &&
      isLeftFlag == rhs.isLeftFlag)
    return true;
  else
    return false;
}
bool RGPHalfSegment2D::operator!=(const RGPHalfSegment2D &rhs) {
  return !((*this) == rhs);
}
bool RGPHalfSegment2D::operator<(const RGPHalfSegment2D &rhs) {
  if (dominantPoint < rhs.dominantPoint ||
      (dominantPoint == rhs.dominantPoint && isLeftFlag == false &&
       rhs.isLeftFlag == true) ||
      (dominantPoint == rhs.dominantPoint && isLeftFlag == rhs.isLeftFlag &&
       m < rhs.m) ||
      (dominantPoint == rhs.dominantPoint && isLeftFlag == rhs.isLeftFlag &&
       m == rhs.m && sqLen() < rhs.sqLen())) {
    return true;
  } else
    return false;
}
bool RGPHalfSegment2D::operator<=(const RGPHalfSegment2D &rhs) {
  return (*this) == rhs || (*this) < rhs;
}
bool RGPHalfSegment2D::operator>(const RGPHalfSegment2D &rhs) {
  return !((*this) <= rhs);
}
bool RGPHalfSegment2D::operator>=(const RGPHalfSegment2D &rhs) {
  return !((*this) < rhs);
}

bool RGPHalfSegment2D::isLeft() { return isLeftFlag; }

Number RGPHalfSegment2D::sqLen() const {
  return (segment.point1.x - segment.point2.x) *
             (segment.point1.x - segment.point2.x) +
         (segment.point1.y - segment.point2.y) *
             (segment.point1.y - segment.point2.y);
}

// RGPAnnotatedHalfSegment2D
// Constructors

RGPAnnotatedHalfSegment2D::RGPAnnotatedHalfSegment2D(RGPSegment2D s,
                                                     RGPPoint2D dp,
                                                     bool regAbove)
    : RGPHalfSegment2D::RGPHalfSegment2D(s, dp) {
  this->insideIsAbove = regAbove;
}

RGPAnnotatedHalfSegment2D::~RGPAnnotatedHalfSegment2D() {}
