#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>


#include "../../include/RGPPoint2D.h"
#include "../../include/ConvexHull/Utils.h"


int orientation(RGPPoint2D* p, RGPPoint2D* q, RGPPoint2D* r)
{
	Number val = (q->y - p->y) * (r->x - q->x) - (q->x - p->x) * (r->y - q->y);
	Number zero_val;
	if (val == zero_val)
		return 0; // collinear
	return (val > zero_val) ? 1 : 2; // clock or counterclock wise
}

/*
 * Intenal method to compute convex hull using Jarvis March method
 */
std::vector < RGPPoint2D* > getConvexHullJarvisMarchInternal(std::vector < RGPPoint2D* >& points) {
   	std::vector < RGPPoint2D* > convexHull;
	// There must be at least 3 points
	int n = points.size();
	if (n < 3){
        std::cout <<"Insuffiecient points";
		return convexHull ;
    }

	// Find the leftmost point and among leftmost point the bottom most point
	int l = 0;
	for (int i = 1; i < n; i++){
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
		// std::cout << "p: " << p << "q: " << q << std::endl;	
		for (int i = (q + 1) % n, j = 0; j < n - 1; i = (i + 1) % n, j++) {
			// If i is more counterclockwise than current q, then update q 
			if (orientation(points[p], points[i], points[q]) == 2)
				q = i;
            // TODO: to implement distance here
            // else if(orientation(points[p], points[i], points[q]) == 0)
                // q = i;
        }

		convexHull.push_back(points[q]);
		
		p = q; // Set p as q for next iteration
	} while (p != l);


	return convexHull;
}

std::vector < RGPPoint2D* > getConvexHullJarvisMarch(std::vector < RGPPoint2D* > points) {
    std::vector < RGPPoint2D* > pointsCopy(points);
    std::sort(pointsCopy.begin(), pointsCopy.end(), pointsComparator());

    std::vector < RGPPoint2D* > convexHullPoints = getConvexHullJarvisMarchInternal(pointsCopy);
    return convexHullPoints;
}