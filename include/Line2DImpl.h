#ifndef LINE2DIMPL_H
#define LINE2DIMPL_H

#include "RGP.h"
#include "STO.h"
#include <vector>

class Line2DImpl : public Line2D {
public:

    std::vector<RGPHalfSegment2D>* getSequence();

private:

    std::vector<RGPHalfSegment2D> sequence;
};

#endif //LINE2DIMPL_H
