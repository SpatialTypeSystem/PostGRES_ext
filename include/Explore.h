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
    void explore(Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
};

#endif
