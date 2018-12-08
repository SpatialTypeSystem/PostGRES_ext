#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "../../include/ConvexHull/Utils.h"
#include "../../include/RGPPoint2D.h"

/*
 * Intenal method to compute convex hull using Jarvis March method
 */
std::vector<RGPPoint2D *> getConvexHullJarvisMarchInternal(std::vector<RGPPoint2D *> &points)
{
  std::vector<RGPPoint2D *> convexHull;
  // There must be at least 3 points
  int n = points.size();
  if (n < 3)
  {
    std::cout << "Insuffiecient points";
    return convexHull;
  }

  // Find the leftmost point and among leftmost point the bottom most point
  int l = 0;
  for (int i = 1; i < n; i++)
  {
    if (points[i]->x < points[l]->x)
      l = i;
    else if ((points[i]->x == points[l]->x) && (points[i]->y < points[l]->y))
      l = i;
  }

  // Start from leftmost point and among leftmost point the bottom most point,
  // keep moving counterclockwise until you reach the start point again
  int p = l, q;
  do
  {
    q = (p + 1) % n;
    // for (int i = (q + 1) % n, j = 0; j < n - 1; i = (i + 1) % n, j++)
    for (int i = 0; i < n; i++)
    {
      // If i is more counterclockwise than current q, then update q
      if (getPositionOfPoint(points[p], points[i], points[q]) == 1)
      {
        q = i;
      }
      else if (getPositionOfPoint(points[p], points[i], points[q]) == 0)
      {
        Number val1 = distanceSquare(points[p], points[q]);
        Number val2 = distanceSquare(points[p], points[i]);
        if (val2 > val1)
        {
          q = i;
        }
      }
    }

    convexHull.push_back(points[q]);

    // Set p as q for next iteration
    p = q;
  } while (p != l);

  return convexHull;
}

std::vector<RGPPoint2D *> getConvexHullJarvisMarch(std::vector<RGPPoint2D *> &points)
{
  std::vector<RGPPoint2D *> pointsCopy(points);
  std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

  std::vector<RGPPoint2D *> convexHullPoints = getConvexHullJarvisMarchInternal(pointsCopy);
  return convexHullPoints;
}