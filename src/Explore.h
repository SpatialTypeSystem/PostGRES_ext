#ifndef EXPLORE_H
#define EXPLORE_H

#include "Point2D.h"
#include "Line2D.h"
#include "Region2D.h"
#include "../include/PlaneSweep.h"
#include <vector>

class Explore
{
public:
    Explore();
    ~Explore();

    // F and G are spatial objects where F is of same or lower dimension then G
    void explore(Point2D  &spatialObj_F, Point2D   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Point2D  &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Point2D  &spatialObj_F, Region2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Line2D   &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Line2D   &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
    void explore(Region2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
};

#endif
