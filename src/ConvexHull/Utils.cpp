#include "../../include/RGPPoint2D.h"

/*
 * +1 : if p3 is left of line (p1, p2)
 * 0 : if p3 is on line (p1, p2)
 * -1 : if p3 is right of line (p1, p2)
 */
int getPositionOfPoint(RGPPoint2D* p1, RGPPoint2D* p2, RGPPoint2D* p3) {
    // Calculates determinant of the below matrix
    // │x1  y1  1│
    // │x2  y2  1│
    // │x3  y3  1│
    Number position(p1->x * p2->y - p1->x * p3->y
                    - p1->y * p2->x + p1->y * p3->x
                    + p2->x * p3->y - p3->x * p2->y);
    Number one("1");
    Number minusOne("-1");
    if (position > one)
        return 1;
    if (position < minusOne)
        return -1;

    return 0;
}