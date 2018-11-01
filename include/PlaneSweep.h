#ifndef PLANESWEEP_H
#define PLANESWEEP_H

#include "RGP.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Region2D.h"
#include <vector>
#include <queue>

class PlaneSweep {
public:
	PlaneSweep();
	~PlaneSweep();
private:

    std::queue<RGPPoint2D> event_point_schedule;	// Stores event points

    void new_sweep(); // Creates a new empty sweep line status
    void add_left(RGPHalfSegment2D left_half); // Adds a segment to the sweep line status when a left half segment is encountered
    void del_right(RGPHalfSegment2D right_half); // Removes a segment from the sweep line status when it's right half segment is encountered

	// Object - SmallestSelected
	enum SmallestSelected { first, second, both, none};
	// Status - SweepStatus
	enum SweepStatus { end_of_first, end_of_second, end_of_both, end_of_none};

	// F and G are spatial objects where F is of same or lower dimension then G
	void explore(Point2D  &spatialObj_F, Point2D   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Point2D  &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Point2D  &spatialObj_F, Region2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Line2D   &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Line2D   &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Region2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);

	Point2D select_next(Point2D  &spatialObj_F, Point2D   &spatialObj_G, SmallestSelected object, SweepStatus status);
	Point2D select_next(Point2D  &spatialObj_F, Line2D    &spatialObj_G, SmallestSelected object, SweepStatus status);
	Point2D select_next(Point2D  &spatialObj_F, Region2D &spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Line2D &spatialObj_F, Line2D &spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Line2D &spatialObj_F, Region2D  &spatialObj_G, SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_next(Region2D &spatialObj_F, Region2D  &spatialObj_G, SmallestSelected object, SweepStatus status);

	Point2D select_first(Point2D  &spatialObj_F, Point2D   &spatialObj_G,SmallestSelected object, SweepStatus status);
	Point2D select_first(Point2D  &spatialObj_F, Line2D    &spatialObj_G,SmallestSelected object, SweepStatus status);
	Point2D select_first(Point2D  &spatialObj_F, Region2D &spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Line2D &spatialObj_F, Line2D &spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Line2D &spatialObj_F, Region2D  &spatialObj_G,SmallestSelected object, SweepStatus status);
	RGPHalfSegment2D select_first(Region2D &spatialObj_F, Region2D  &spatialObj_G,SmallestSelected object, SweepStatus status);
};

#endif //PLANESWEEP