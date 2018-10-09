/* This is a universal header for all Robust Geometric Primitives. Users
 * looking only for specific aspects of the RGP implementation should include
 * headers for those instead.
 */

#ifndef RGPOPERATIONS2D_H
#define RGPOPERATIONS2D_H

// Optional definition
#ifdef __has_include

// Check for standard library
#  if __has_include(<optional>)
#    include<optional>
     using std::optional;

// Check for exprimental version (bug fix for Xcode on macOS)
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
     using std::experimental::optional;

// Not found
#  else
#     error "Missing <optional>"
#  endif
#endif


#include "RGPPoint2D.h"
#include "RGPSegment2D.h"
#include "RGPHalfSegment2D.h"

class RGPOperations2D
{
public:

    static bool intersecting(RGPSegment2D s1, RGPSegment2D s2);

    static optional <RGPPoint2D> intersectionOf(RGPSegment2D s1,
        RGPSegment2D s2);

private:

    static Number orientation(RGPPoint2D p1, RGPPoint2D p2, RGPPoint2D p3);
};

#endif //RGPOPERATIONS2D_H
