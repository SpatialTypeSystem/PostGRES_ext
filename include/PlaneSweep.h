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

template<class F, class G>
class PlaneSweep {
public:

	PlaneSweep(std::vector<F>::iterator startIteratorF, std::vector<F>::iterator endIteratorF, std::vector<G>::iterator startIteratorG, std::vector<G>::iterator endIteratorG);

    ObjectSelected object;
    TraversalStatus status;

    PlaneSweep(const std::vector<F>& seqF, const std::vector<G>& seqG);
    ~PlaneSweep();

    void select_first();
    void select_next();

    // Get event returns the element to which the logical pointer of a point
    // or half segment sequence of an object points to
    typename std::vector<F>::const_iterator getEventF();
    typename std::vector<G>::const_iterator getEventG();

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

    // Returns the nearest annotated halfsegment, from the sweep line status, below a given point, if there is one
    optional<bool> getAttributeOfSegmentBelow(RGPPoint2D p);
    // Returns the overlap numbers of the predecessor to the given segment in the sweep line status
    optional<std::tuple<short, short>> getOverlapNumbersOfPredecessor(RGPSegment2D s);
    // Returns the overlap numbers of the given segment in the sweep line status
    optional<std::tuple<short, short>> getOverlapNumbersOf(RGPSegment2D s);

private:
    // Stores event points
    std::queue<RGPPoint2D> eventPointSchedule;

    template <class obj>
    // Holds the state of the intersection of the sweep line
    AVLtree<obj> sweepLineStatus;
    //Sets an attribute for a segment in the sweep line status
    void set_attr(AVLtree<obj>             &sweepLineStatus, bool attribute);
    //Gets an attribute from a segment in the sweep line status
    bool get_attr(AVLtree<obj>             &sweepLineStatus);
    //Yields the attribute from the prdecessor of a segment in the sweepline status
    bool get_pred_attr(AVLtree<obj>        &sweepLineStatus, RGPHalfSegment2D segment);
    //Checks for a segment in the sweepLineStatus to check if it hasa predecessor
    bool pred_exists(AVLtree<obj>          &sweepLineStatus, RGPHalfSegment2D segment);
    //Checks for a neighbor segment
    bool common_point_exists(AVLtree<obj>  &sweepLineStatus, RGPHalfSegment2D segment);
    //Tests whether such a segment exists
    bool current_exists(AVLtree<obj>       &sweepLineStatus);

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

// Methods

template<class F, class G>
inline
PlaneSweep<F,G>::PlaneSweep(std::vector<F>::iterator startIteratorF, std::vector<F>::iterator endIteratorF, std::vector<G>::iterator startIteratorG, std::vector<G>::iterator endIteratorG) :
	staticIteratorF(startIteratorF), endStaticIteratorF(endIteratorF), startIteratorG(startIteratorG), endStaticIteratorG(endIteratorG)
{
    object = ObjectSelected::NONE;
    status = TraversalStatus::END_OF_NONE;
}

template<class F, class G>
inline
PlaneSweep<F,G>::~PlaneSweep()
{

}

template<class F, class G>
inline
void PlaneSweep<F,G>::select_first()
{
    if (!staticSequenceF.empty())
    {
        if (!staticSequenceG.empty())
        {
            if ((*staticIteratorG) > (*staticIteratorF))
            {
                object = ObjectSelected::OBJ_F;
            }
            else if ((*staticIteratorG) < (*staticIteratorF))
            {
                object = ObjectSelected::OBJ_G;
            }
            else
            {
                object = ObjectSelected::BOTH;
            }
            status = TraversalStatus::END_OF_NONE;
        }
        else
        {
            status = TraversalStatus::END_OF_G;
        }
    }
    else if (!staticSequenceG.empty())
    {
        status = TraversalStatus::END_OF_F;
    }
    else
    {
        status = TraversalStatus::END_OF_BOTH;
    }

    return;
}

template<class F, class G>
inline
void PlaneSweep<F,G>::select_next() {
    if (object == ObjectSelected::OBJ_F)
    {
        if (++staticIteratorF < endStaticIteratorF)
        {
            if (status != TraversalStatus::END_OF_G)
            {
                if ( (*staticIteratorG) > (*staticIteratorF))
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if ((*staticIteratorG) < (*staticIteratorF))
                {
                    object = ObjectSelected::OBJ_G;
                }
                else
                {
                    object = ObjectSelected::BOTH;
                }
            }
            else
            {
                object = ObjectSelected::OBJ_F;
            }
        }
        else
        {
            if (status == TraversalStatus::END_OF_G)
            {
                object = ObjectSelected::NONE;
                status = TraversalStatus::END_OF_BOTH;
            }
            else
            {
                object = ObjectSelected::OBJ_G;
                status = TraversalStatus::END_OF_F;
            }
        }
    }
    else if (object == ObjectSelected::OBJ_G)
    {
        if (++staticIteratorG < endStaticIteratorG)
        {
            if (status != TraversalStatus::END_OF_F)
            {
                if ((*staticIteratorG) > (*staticIteratorF))
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if ((*staticIteratorG) < (*staticIteratorF))
                {
                    object = ObjectSelected::OBJ_G;
                }
                else
                {
                    object = ObjectSelected::BOTH;
                }
            }
            else
            {
                object = ObjectSelected::OBJ_G;
            }
        }
        else
        {
            if (status == TraversalStatus::END_OF_F)
            {
                object = ObjectSelected::NONE;
                status = TraversalStatus::END_OF_BOTH;
            }
            else
            {
                object = ObjectSelected::OBJ_F;
                status = TraversalStatus::END_OF_G;
            }
        }
    }
    else if (object == ObjectSelected::BOTH)
    {
        ++staticIteratorF;
        ++staticIteratorG;

        bool check_F = staticIteratorF < endStaticIteratorF;
        bool check_G = staticIteratorG < endStaticIteratorG;

        if (check_F && check_G)
        {
            if ((*staticIteratorG) > (*staticIteratorF))
            {
                object = ObjectSelected::OBJ_F;
            }
            else if ((*staticIteratorG) < (*staticIteratorF))
            {
                object = ObjectSelected::OBJ_G;
            }
            else
            {
                object = ObjectSelected::BOTH;
            }
        }
        else if (check_F)
        {
            object = ObjectSelected::OBJ_F;
            status = TraversalStatus::END_OF_G;
        }
        else if (check_G)
        {
            object = ObjectSelected::OBJ_G;
            status = TraversalStatus::END_OF_F;
        }
        else
        {
            object = ObjectSelected::NONE;
            status = TraversalStatus::END_OF_BOTH;
        }
    }
}

template <class F, class G>
inline

F PlaneSweep<F,G>::getEventF()
{
    // Get event returns the element to which the logical pointer of a
    // point or half segment sequence of an object points to
    return *staticIteratorF;
}

template <class F, class G>
inline
G PlaneSweep<F,G>::getEventG()
{
    // Get event returns the element to which the logical pointer of a
    // point or half segment sequence of an object points to
    return *staticIteratorG;
}

template <class F, class G>
inline
bool PlaneSweep<F,G>::pointOnSegment(RGPPoint2D p)
{

}

template <class F, class G>
inline
bool PlaneSweep<F,G>::pointInSegment(RGPPoint2D p)
{

}

template <class F, class G>
inline
void PlaneSweep<F,G>::insert(RGPSegment2D s)
{
    // Inserts/Removes a segment from the sweep line status when
    // it's left/right half segment is encountered
}

template <class F, class G>
inline
void PlaneSweep<F,G>::remove(RGPSegment2D s)
{
    // Inserts/Removes a segment from the sweep line status when
    // it's left/right half segment is encountered
}

template <class F, class G>
inline
bool PlaneSweep<F,G>::lookAheadF(RGPHalfSegment2D h)
{
    // Check if the dominant points of the given halfsegment and the next
    // halfsegment (after the current index) of the indicated sequence are equal
    if (staticIteratorF == endStaticIteratorF) {
        return (*++staticIteratorF) == h;
    } else {
        return false;
    }
}

template <class F, class G>
inline
bool PlaneSweep<F,G>::lookAheadG(RGPHalfSegment2D h)
{
    // Check if the dominant points of the given halfsegment and the next
    // halfsegment (after the current index) of the indicated sequence are equal
    if (staticIteratorG == endStaticIteratorG) {
        return (*++staticIteratorG) == h;
    } else {
        return false;
    }
}

template <class F, class G>
inline
optional<bool> PlaneSweep<F,G>::getAttributeOfSegmentBelow(RGPPoint2D p)
{
    // Returns the nearest annotated halfsegment, from the sweep line status,
    // below a given point, if there is one

    // Loops through sweep line status, checking if the segment is classified as less than our RGPPoint2D
    // Returns the first one that is true
}

template <class F, class G>
inline
optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOfPredecessor(RGPSegment2D s)
{
    // Returns the overlap numbers of the predecessor to the given segment in the sweep line status
}

template <class F, class G>
inline
optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOf(RGPSegment2D s)
{
    // Returns the overlap numbers of the given segment in the sweep line status
}
#endif //PLANESWEEP
