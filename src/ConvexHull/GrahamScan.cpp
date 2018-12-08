#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

// A utility function to find next to top in a stack
RGPPoint2D *nextToTop(std::stack<RGPPoint2D *> &S)
{
  RGPPoint2D *p = S.top();
  S.pop();
  RGPPoint2D *res = S.top();
  S.push(p);

  return res;
}

struct pointsComparatorGraham
{
  pointsComparatorGraham(RGPPoint2D **p0)
  {
    this->p0 = p0;
  }

  inline bool operator()(const RGPPoint2D *p1, const RGPPoint2D *p2)
  {
    int o = getPositionOfPoint(*p0, p1, p2);
    if (o == 0)
      return (distanceSquare(*p0, p2) >= distanceSquare(*p0, p1)) ? false : true;

    return o < 0 ? true : false;
  }

  RGPPoint2D **p0;
};

// PrNumbers convex hull of a set of n RGPPoint2Ds.
std::vector<RGPPoint2D *> getGraham(std::vector<RGPPoint2D *> &RGPPoint2DsOriginal)
{
  std::vector<RGPPoint2D *> RGPPoint2Ds(RGPPoint2DsOriginal);
  int n = RGPPoint2Ds.size();

  // Find the bottommost RGPPoint2D
  int min = 0;
  for (int i = 1; i < n; i++)
  {
    // Pick the bottom-most or chose the left
    // most RGPPoint2D in case of tie
    if ((RGPPoint2Ds[i]->y < RGPPoint2Ds[min]->y) ||
        (RGPPoint2Ds[i]->y == RGPPoint2Ds[min]->y && RGPPoint2Ds[i]->x < RGPPoint2Ds[min]->x))
    {
      min = i;
    }
  }

  // Place the bottom-most RGPPoint2D at first position
  swap(RGPPoint2Ds, 0, min);

  // Sort n-1 RGPPoint2Ds with respect to the first RGPPoint2D.
  // A RGPPoint2D p1 comes before p2 in sorted ouput if p2
  // has larger polar angle (in counterclockwise
  // direction) than p1
  sort(RGPPoint2Ds.begin() + 1, RGPPoint2Ds.end(), pointsComparatorGraham(&RGPPoint2Ds[0]));

  if (n < 3)
  {
    std::vector<RGPPoint2D *> convexHull = getConvexHullBruteForce(RGPPoint2Ds);
    // printPoints1(convexHull);
    return convexHull;
  }

  // Create an empty stack and push first three RGPPoint2Ds to it.
  std::stack<RGPPoint2D *> S;
  S.push(RGPPoint2Ds[0]);
  S.push(RGPPoint2Ds[1]);
  S.push(RGPPoint2Ds[2]);

  // Process remaining n-3 RGPPoint2Ds
  for (int i = 3; i < n; i++)
  {
    // Keep removing top while the angle formed by
    // RGPPoint2Ds next-to-top, top, and RGPPoint2Ds[i] makes
    // a non-left turn
    while ((int)S.size() > 1 && getPositionOfPoint(nextToTop(S), S.top(), RGPPoint2Ds[i]) != -1)
    {
      S.pop();
    }

    S.push(RGPPoint2Ds[i]);
  }

  if ((int)S.size() > 2)
  {
    if (getPositionOfPoint(nextToTop(S), S.top(), RGPPoint2Ds[0]) == 0)
    {
      S.pop();
    }
  }

  std::vector<RGPPoint2D *> convexHull((int)S.size(), NULL);

  // Now stack has the output RGPPoint2Ds, prNumber contents of stack
  while (!S.empty())
  {
    RGPPoint2D *p = S.top();
    convexHull[(int)S.size() - 1] = p;
    S.pop();
  }

  return convexHull;
}