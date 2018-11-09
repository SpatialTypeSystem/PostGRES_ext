#ifndef POINT2DIMPL_H
#define POINT2DIMPL_H

#include "RGP.h"
#include "STO.h"
#include <vector>

class Point2DImpl : public Point2D {
public:

    std::vector<RGPPoint2D>* getSequence();

private:

    std::vector<RGPPoint2D> sequence;
};

#endif //POINT2DIMPL_H
