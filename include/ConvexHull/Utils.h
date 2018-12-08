#include "../../include/Number.h"
#include "../../include/RGPPoint2D.h"

/*
 * A utility function to return square of distance 
 * between p1 and p2
 */
Number distanceSquare(const RGPPoint2D* p1, const RGPPoint2D* p2);

/*
 * Computes convex hull of points in
 * near constant time when number of points <= 3
 */
std::vector < RGPPoint2D* > getConvexHullBruteForce(std::vector < RGPPoint2D* > points);

/*
 * +1 : if p3 is left of line (p1, p2)
 * 0 : if p3 is on line (p1, p2)
 * -1 : if p3 is right of line (p1, p2)
 */
int getPositionOfPoint(const RGPPoint2D* p1, const RGPPoint2D* p2, const RGPPoint2D* p3);

void swap(std::vector< RGPPoint2D * >& RGPPoint2Ds, int a, int b);

/*
 * Comparator to compare points consisting of x and y coordinates
 * returns true if x coordinate of x point is less than x coordinate of y point
 * or if y coordinate of x point is less than y coordinate of y point when the x coordinates are equal
 */
struct pointsComparator
{
    inline bool operator() (const RGPPoint2D* a, const RGPPoint2D* b)
    {
        // std::cout << a->x << std::endl;
        // std::cout << a->x << " " << a->y << " " << b->x << " " << b->y << std::endl;
        if (a->x == b->x)
            return a->y < b->y;

        return a->x < b->x;
    }
};