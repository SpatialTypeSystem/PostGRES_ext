#include <iostream>
#include <stack>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;

#include "../../include/RGPPoint2D.h"

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the RGPPoint2Ds are collinear.
Number cross(RGPPoint2D *O, RGPPoint2D *A, RGPPoint2D *B)
{
  return (A->x - O->x) * (B->y - O->y) - (A->y - O->y) * (B->x - O->x);
}

// Returns a list of RGPPoint2Ds on the convex hull in counter-clockwise order.
// Note: the last RGPPoint2D in the returned list is the same as the first one.
std::vector<RGPPoint2D *> getMonotone(std::vector<RGPPoint2D *> &P)
{
  int n = P.size(), k = 0;
  Number zero("0");
  if (n <= 3)
    return P;
  std::vector<RGPPoint2D *> H(2 * n);

  // Sort RGPPoint2Ds lexicographically
  sort(P.begin(), P.end());

  // Build lower hull
  for (int i = 0; i < n; ++i)
  {
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= zero)
      k--;
    H[k++] = P[i];
  }

  // Build upper hull
  for (int i = n - 1, t = k + 1; i > 0; --i)
  {
    while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= zero)
      k--;
    H[k++] = P[i - 1];
  }

  H.resize(k - 1);
  return H;
}
