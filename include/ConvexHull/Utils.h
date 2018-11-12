#include "../../include/RGPPoint2D.h"

int getPositionOfPoint(RGPPoint2D* p1, RGPPoint2D* p2, RGPPoint2D* p3);

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