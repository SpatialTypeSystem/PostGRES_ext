#include "PlaneSweep.h"

class PlaneSweep {
public:

private:
// Explore
	void Explore(Point2D  spatialObj_F, Point2D   spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

	void Explore(Point2D  spatialObj_F, Line2D    spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

	void Explore(Point2D  spatialObj_F, Segment2D spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

	void Explore(SegmentD spatialObj_F, Segment2D spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

	void Explore(SegmentD spatialObj_F, Region2D  spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

	void Explore(Region2D spatialObj_F, Region2D  spatialObj_G, bool[] &featureVectorF, bool[] &featureVectorG)
	{

	}

// Select Next
	Point2D select_next(Point2D  spatialObj_F, Point2D   spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}

	Point2D select_next(Point2D  spatialObj_F, Line2D    spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}
	
	Point2D select_next(Point2D  spatialObj_F, Line2D spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_next(Line2D spatialObj_F, Line2D spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_next(Line2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_next(Region2D spatialObj_F, Region2D  spatialObj_G, SmallestSelected object, SweepStatus status)
	{

	}

// Select first
	Point2D select_first(Point2D  spatialObj_F, Point2D   spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}

	Point2D select_first(Point2D  spatialObj_F, Line2D    spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}

	Point2D select_first(Point2D  spatialObj_F, Line2D spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_first(Line2D spatialObj_F, Line2D spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_first(Line2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}

	RGPHalfSegment2D select_first(Region2D spatialObj_F, Region2D  spatialObj_G,SmallestSelected object, SweepStatus status)
	{

	}
}