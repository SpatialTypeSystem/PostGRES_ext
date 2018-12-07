#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"


// A utility function to find next to top in a stack
RGPPoint2D *nextToTop(std::stack< RGPPoint2D * >& S)
{
  RGPPoint2D *p = S.top();
  S.pop();
  RGPPoint2D *res = S.top();
  S.push(p);

  return res;
}

// A utility function to swap two RGPPoint2Ds
void swap(std::vector< RGPPoint2D * >& RGPPoint2Ds, int a, int b)
{
  if (a == b)
  {
    return;
  }

  RGPPoint2D *temp = RGPPoint2Ds[a];
  RGPPoint2Ds[a] = RGPPoint2Ds[b];
  RGPPoint2Ds[b] = temp;
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
std::vector< RGPPoint2D * > getGraham(std::vector< RGPPoint2D * > RGPPoint2DsOriginal)
{
  std::vector< RGPPoint2D * > RGPPoint2Ds(RGPPoint2DsOriginal);

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

  // If two or more RGPPoint2Ds make same angle with p0,
  // Remove all but the one that is farthest from p0
  // Remember that, in above sorting, our criteria was
  // to keep the farthest RGPPoint2D at the end when more than
  // one RGPPoint2Ds have same angle.
  int m = 1; // Initialize size of modified array
  for (int i = 1; i < n; i++)
  {
    // Keep removing i while angle of i and i+1 is same
    // with respect to p0
    while (i < n - 1 && getPositionOfPoint(RGPPoint2Ds[0], RGPPoint2Ds[i],
                                           RGPPoint2Ds[i + 1]) == 0)
    {
      i++;
    }

    if (m != i)
    {
      RGPPoint2Ds[m] = RGPPoint2Ds[i];
    }

    // Update size of modified array
    m++; 
  }

  while (RGPPoint2Ds.size() > m)
    RGPPoint2Ds.pop_back();

  // If modified array of RGPPoint2Ds has less than 3 RGPPoint2Ds,
  // convex hull is not possible
  if (m < 3)
  {
    //    std::vector < RGPPoint2D* > convexHull;
    return getConvexHullBruteForce(RGPPoint2Ds);
  }

  // Create an empty stack and push first three RGPPoint2Ds to it.
  std::stack< RGPPoint2D * > S;
  S.push(RGPPoint2Ds[0]);
  S.push(RGPPoint2Ds[1]);
  S.push(RGPPoint2Ds[2]);

  // Process remaining n-3 RGPPoint2Ds
  for (int i = 3; i < m; i++)
  {
    // Keep removing top while the angle formed by
    // RGPPoint2Ds next-to-top, top, and RGPPoint2Ds[i] makes
    // a non-left turn
    while (getPositionOfPoint(nextToTop(S), S.top(), RGPPoint2Ds[i]) != -1)
    {
      S.pop();
    }

    S.push(RGPPoint2Ds[i]);
  }

  std::vector< RGPPoint2D * > convexHull((int)S.size(), NULL);
  
  // Now stack has the output RGPPoint2Ds, prNumber contents of stack
  while (!S.empty())
  {
    RGPPoint2D *p = S.top();
    convexHull[(int)S.size() - 1] = p;
    S.pop();
  }

  return convexHull;
}