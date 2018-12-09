#ifndef EXPLORE_H
#define EXPLORE_H

#include "RGP.h"
#include "../include/Point2DImpl.h"
#include "Line2DImpl.h"
#include "Region2DImpl.h"
#include "PlaneSweep.h"
#include <vector>

class Explore
{
public:
    Explore();
    ~Explore();

    // F and G are spatial objects where F is of same or lower dimension then G
    void explore(std::vector<RGPPoint2D>::iterator pointerObj_F, std::vector<RGPPoint2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(std::vector<RGPPoint2D>::iterator pointerObj_F, std::vector<RGPHalfSegment2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);    
    void explore(std::vector<RGPPoint2D>::iterator pointerObj_F, std::vector<RGPAnnotatedHalfSegment2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(std::vector<RGPHalfSegment2D>::iterator pointerObj_F, std::vector<RGPHalfSegment2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(std::vector<RGPHalfSegment2D>::iterator pointerObj_F, std::vector<RGPAnnotatedHalfSegment2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(std::vector<RGPAnnotatedHalfSegment2D>::iterator pointerObj_F, std::vector<RGPAnnotatedHalfSegment2D>::iterator pointerObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);

private:

    void setOverlapFlag(int& flag, int m, int n);
};

#endif
