#ifndef REGION2DIMPL_H
#define REGION2DIMPL_H

#include "RGP.h"
#include "Region2D.h"
#include <vector>

class Region2DImpl : public Region2D {
public:

    Region2DImpl();
    ~Region2DImpl();

    std::vector<RGPAnnotatedHalfSegment2D>* getSequence();

private:

    std::vector<RGPAnnotatedHalfSegment2D> sequence;
};

#endif //REGION2DIMPL_H
