#ifndef POINT2DIMPL_H
#define POINT2DIMPL_H

#include "RGP.h"
#include "Point2D.h"
#include <vector>

class Point2DImpl : public Point2D {
public:
    Point2DImpl();
    ~Point2DImpl();

    std::vector<RGPPoint2D>* getSequence();

private:

    std::vector<RGPPoint2D> sequence;
};

#endif //POINT2DIMPL_H
