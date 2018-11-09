#ifndef PLANESWEEP_H
#define PLANESWEEP_H

#include "RGP.h"
#include <vector>
#include <queue>

// Object - ObjectSelected
enum class ObjectSelected {OBJ_F, OBJ_G, BOTH, NONE};
// Status - TraversalStatus
enum class TraversalStatus {END_OF_F, END_OF_G, END_OF_BOTH, END_OF_NONE};

template<class F, class G>
class PlaneSweep {
public:

    ObjectSelected object;
    TraversalStatus status;

    PlaneSweep(std::vector<F>* seqF, std::vector<G>* seqG);
    ~PlaneSweep();

    void select_first();
    void select_next();

private:
    // Pointers to the spatial object sequences
    const std::vector<F>* sequenceF;
    const std::vector<G>* sequenceG;

    // Sequence sizes
    const int sizeF;
    const int sizeG;

    // Sequence index trackers
    int indexF;
    int indexG;

    //// NON-TEMPLATED CODE ////

//    std::queue<RGPPoint2D> eventPointSchedule;  // Stores event points
//
//    struct SweepLineStatus; //Holds the state of the intersection of the sweep line
//
//    SweepLineStatus new_sweep(); // Creates a new empty sweep line status
//    void add_left(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D leftHalf); // Adds a segment to the sweep line status when a left half segment is encountered
//    void del_right(SweepLineStatus &sweepLineStatus,RGPHalfSegment2D rightHalf); // Removes a segment from the sweep line status when it's right half segment is encountered
//    void set_attr(SweepLineStatus &sweepLineStatus, bool attribute);  //Sets an attribute for a segment in the sweep line status
//    bool get_attr(SweepLineStatus &sweepLineStatus);	//Gets an attribute from a segment in the sweep line status
//    bool get_pred_attr(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Yields the attribute from the prdecessor of a segment in the sweepline status
//    bool pred_exists(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Checks for a segment in the sweepLineStatus to check if it hasa predecessor
//    bool common_point_exists(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Checks for a neighbor segment
//    RGPSegment2D pred_of_p(SweepLineStatus &sweepLineStatus,RGPPoint2D point); //Searches the nearest segment below a given point in the sweepLineStatus
//    bool current_exists(SweepLineStatus &sweepLineStatus); //Tests whether such a segment exists
//    bool poi_on_seg(SweepLineStatus &sweepLineStatus,RGPPoint2D point); //Checks whether a given point lies on any segment of the sweepLineStatus
//    bool look_ahead(RGPHalfSegment2D currentHalfSegement, Line2D &spatialObject); //Checks if sequence between previous point and next point of current and next half segments are equal
//
//
//    // Get event returns the element to which the logical pointer of a point or half segment sequence of an object points to
//    RGPPoint2D get_event(Point2D &spatialObj);
//    // RGPPoint2D get_event_G(Point2D &spatialObj_G);
//    RGPHalfSegment2D get_event(Line2D &spatialObj);
//    // RGPHalfSegment2D get_event_G(Line2D &spatialObj_G);
//    RGPAnnotatedHalfSegment2D get_event(Region2D &spatialObj);
//    // RGPAnnotatedHalfSegment2D get_event_G(Region2D &spatialObj_G);
};

#endif //PLANESWEEP
