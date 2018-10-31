#include "RGP.h"

#ifndef PLANESWEEP_H
#define PLANESWEEP_H

class PlaneSweep {
public:

private:
	// F and G are spatial objects where F is of same or lower dimension then G
	void Explore(Point2D  spatialObj_F, Point2D   spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);
	void Explore(Point2D  spatialObj_F, Line2D    spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);
	void Explore(Point2D  spatialObj_F, Line2D    spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);
	void Explore(Line2D   spatialObj_F, Line2D    spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);
	void Explore(Line2D   spatialObj_F, Region2D  spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);
	void Explore(Region2D spatialObj_F, Region2D  spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG);

	Point2D select_next(Point2D  spatialObj_F, Point2D   spatialObj_G, SmallestSelected object, SweepStatus status);
	Point2D select_next(Point2D  spatialObj_F, Line2D    spatialObj_G, SmallestSelected object, SweepStatus status);
	Point2D select_next(Point2D  spatialObj_F, Line2D spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Line2D spatialObj_F, Line2D spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Line2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Region2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status);

	Point2D select_first(Point2D  spatialObj_F, Point2D   spatialObj_G,SmallestSelected object, SweepStatus status);
	Point2D select_first(Point2D  spatialObj_F, Line2D    spatialObj_G,SmallestSelected object, SweepStatus status);
	Point2D select_first(Point2D  spatialObj_F, Line2D spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Line2D spatialObj_F, Line2D spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Line2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Region2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status);

	// Object - SmallestSelected
	enum SmallestSelect { firstObjSmallestSegment = 0, secondObjSmallestSegment = 1, both = 2, none = 3 };
	// Status - SweepStatus
	enum SweepStatus { endOfNone = 0, endOfFirst = 1, endOfSecond = 2, endOfBoth = 3 }
}

#endif //PLANESWEEP