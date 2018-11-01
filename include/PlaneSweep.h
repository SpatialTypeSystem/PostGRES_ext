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
    // Object - ObjectSelected
    enum class ObjectSelected {F, G, BOTH, NONE};
    // Status - TraversalStatus
    enum class TraversalStatus {END_OF_F, END_OF_G, END_OF_BOTH, END_OF_NONE};

    int pointerF, pointerG; // Logical pointers where a value >= 0 indicates an index in the sequence

    std::queue<RGPPoint2D> eventPointSchedule;  // Stores event points

    void new_sweep(); // Creates a new empty sweep line status
    void add_left(RGPHalfSegment2D leftHalf); // Adds a segment to the sweep line status when a left half segment is encountered
    void del_right(RGPHalfSegment2D rightHalf); // Removes a segment from the sweep line status when it's right half segment is encountered

    // Get event returns the element to which the logical pointer of a point or half segment sequence of an object points to
    RGPPoint2D get_event_F(Point2D &spatialObj_F);
    RGPHalfSegment2D get_event_F(Line2D &spatialObj_F);
    RGPHalfSegment2D get_event_G(Line2D &spatialObj_G);
    RGPAnnotatedHalfSegment2D get_event_F(Region2D &spatialObj_F);
    RGPAnnotatedHalfSegment2D get_event_G(Region2D &spatialObj_G);


	// F and G are spatial objects where F is of same or lower dimension then G
	void explore(Point2D  &spatialObj_F, Point2D   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Point2D  &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Point2D  &spatialObj_F, Region2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Line2D   &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Line2D   &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);
	void explore(Region2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG);

	void select_next(Point2D  &spatialObj_F, Point2D   &spatialObj_G, ObjectSelected &object, TraversalStatus &status);
	void select_next(Point2D  &spatialObj_F, Line2D    &spatialObj_G, ObjectSelected &object, TraversalStatus &status);
	void select_next(Point2D  &spatialObj_F, Region2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status);
	void select_next(Line2D &spatialObj_F, Line2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status);
	void select_next(Line2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status);
	void select_next(Region2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status);

	void select_first(Point2D  &spatialObj_F, Point2D   &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
	void select_first(Point2D  &spatialObj_F, Line2D    &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
	void select_first(Point2D  &spatialObj_F, Region2D &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
	void select_first(Line2D &spatialObj_F, Line2D &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
	void select_first(Line2D &spatialObj_F, Region2D  &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
	void select_first(Region2D &spatialObj_F, Region2D  &spatialObj_G,ObjectSelected &object, TraversalStatus &status);
};

#endif //PLANESWEEP