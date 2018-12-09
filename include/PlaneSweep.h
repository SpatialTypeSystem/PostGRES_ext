#ifndef PLANESWEEP_H
#define PLANESWEEP_H

#include "RGP.h"
#include "AVLTree.h"
#include <vector>
#include <queue>
#include <tuple>

// Object - ObjectSelected
enum class ObjectSelected {OBJ_F, OBJ_G, BOTH, NONE};
// Status - TraversalStatus
enum class TraversalStatus {END_OF_F, END_OF_G, END_OF_BOTH, END_OF_NONE};

// template<class T>
// class PointerWrapper{
//
//    PointerWrapper(typename std::vector<T>::iterator dynamicIterator) {
//        myIterator = dynamicIterator;
//    }
//    typename std::vector<T>::iterator myIterator;
//
//    bool operator>(const PointerWrapper &pw)const {
//        return true;
//    }
// };

template<class F, class G>
class PlaneSweep {
public:
	  PlaneSweep(typename std::vector<F>::iterator startIteratorF, typename std::vector<F>::iterator endIteratorF,
      typename std::vector<G>::iterator startIteratorG, typename std::vector<G>::iterator endIteratorG);

    PlaneSweep(const std::vector<F>& seqF, const std::vector<G>& seqG);

    ObjectSelected object;
    TraversalStatus status;

    ~PlaneSweep();

    void select_first();
    void select_next();

    // Get event returns the element to which the logical pointer of a point
    // or half segment sequence of an object points to
    // typename std::vector<F>::const_iterator getEventF();
    // typename std::vector<G>::const_iterator getEventG();
    F getEventF();
    G getEventG();

    // Checks whether a given point lies on/in any segment of the sweep line status
    bool pointOnSegment(RGPPoint2D p);
    bool pointInSegment(RGPPoint2D p);

    // Inserts/Removes a segment from the sweep line status when it's left/right half segment is encountered
    void insert(RGPSegment2D s);
    void remove(RGPSegment2D s);

    // Check if the dominant points of the given halfsegment and the next halfsegment
    // (after the current index) of the indicated sequence are equal
    bool lookAheadF(RGPHalfSegment2D h);
    bool lookAheadG(RGPHalfSegment2D h);

    // Atribute - whether a segment is inside a region
    // Returns the nearest annotated halfsegment, from the sweep line status, below a given point, if there is one
    optional<bool> getAttributeOfSegmentBelow(RGPPoint2D p);
    // Returns the overlap numbers of the predecessor to the given segment in the sweep line status
    optional<std::tuple<short, short>> getOverlapNumbersOfPredecessor(RGPSegment2D s);
    // Returns the overlap numbers of the given segment in the sweep line status
    optional<std::tuple<short, short>> getOverlapNumbersOf(RGPSegment2D s);

private:
    // Stores event points
    std::queue<RGPPoint2D> eventPointSchedule;

    // PointerWrapper() iteratorPtr;
    // Holds the state of the intersection of the sweep line

    AVLtree<RGPSegment2D> sweepLineStatus;
    //Sets an attribute for a segment in the sweep line status
    void set_attr(AVLtree<RGPSegment2D> &sweepLineStatus, bool attribute);
    //Gets an attribute from a segment in the sweep line status
    bool get_attr(AVLtree<RGPSegment2D> &sweepLineStatus);
    //Yields the attribute from the prdecessor of a segment in the sweepline status
    bool get_pred_attr(AVLtree<RGPSegment2D> &sweepLineStatus, RGPHalfSegment2D segment);
    //Checks for a segment in the sweepLineStatus to check if it hasa predecessor
    bool pred_exists(AVLtree<RGPSegment2D> &sweepLineStatus, RGPHalfSegment2D segment);
    //Checks for a neighbor segment
    bool common_point_exists(AVLtree<RGPSegment2D> &sweepLineStatus, RGPHalfSegment2D segment);
    //Tests whether such a segment exists
    bool current_exists(AVLtree<RGPSegment2D> &sweepLineStatus);
    //Stores left segment component into the segment sequence of the sweep line status
    bool add_left();
    //Removes a segment component from the segment sequence of the sweep line status
    bool del_right();
    //Returns new sweep line status
    AVLtree<RGPSegment2D> new_sweep();

    // template<class F, class G>
    // References to the spatial object sequences
    const std::vector<F>& staticSequenceF;
    const std::vector<G>& staticSequenceG;
    std::vector<F> dynamicSequenceF;
    std::vector<G> dynamicSequenceG;
    typename std::vector<F>::iterator staticIteratorF;
    typename std::vector<G>::iterator staticIteratorG;
    // Iterators to check if we are at the end of vector
    // typename std::vector<F>::iterator startStaticIteratorF;
    // typename std::vector<G>::iterator startStaticIteratorG;
    typename std::vector<F>::iterator endStaticIteratorF;
    typename std::vector<G>::iterator endStaticIteratorG;
    typename std::vector<F>::iterator dynamicIteratorF;
    typename std::vector<G>::iterator dynamicIteratorG;

};

#endif //PLANESWEEP
