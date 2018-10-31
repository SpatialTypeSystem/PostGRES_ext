#include "PlaneSweep.h"

PlaneSweep::PlaneSweep()
{

}

PlaneSweep::~PlaneSweep()
{

}

void PlaneSweep::Explore(Point2D  spatialObj_F, Point2D   spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

void PlaneSweep::Explore(Point2D  spatialObj_F, Line2D    spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

void PlaneSweep::Explore(Point2D  spatialObj_F, Region2D spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

void PlaneSweep::Explore(Line2D spatialObj_F, Line2D spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

void PlaneSweep::Explore(Line2D spatialObj_F, Region2D  spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

void PlaneSweep::Explore(Region2D spatialObj_F, Region2D  spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Select Next
Point2D PlaneSweep::select_next(Point2D  spatialObj_F, Point2D   spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

Point2D PlaneSweep::select_next(Point2D  spatialObj_F, Line2D    spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

Point2D PlaneSweep::select_next(Point2D  spatialObj_F, Region2D spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_next(Line2D spatialObj_F, Line2D spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_next(Line2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_next(Region2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status)
{

}

// Select first
Point2D PlaneSweep::select_first(Point2D  spatialObj_F, Point2D   spatialObj_G,SmallestSelected object, SweepStatus status)
{

}

Point2D PlaneSweep::select_first(Point2D  spatialObj_F, Line2D    spatialObj_G,SmallestSelected object, SweepStatus status)
{

}

Point2D PlaneSweep::select_first(Point2D  spatialObj_F, Region2D spatialObj_G,SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_first(Line2D spatialObj_F, Line2D spatialObj_G,SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_first(Line2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status)
{

}

RGPHalfSegment2D PlaneSweep::select_first(Region2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status)
{

}