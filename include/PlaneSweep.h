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

    PlaneSweep(const std::vector<F>& seqF, const std::vector<G>& seqG);
    ~PlaneSweep();

    void select_first();
    void select_next();

    // Get event returns the element to which the logical pointer of a point or half segment sequence of an object points to
    F getEventF();
    G getEventG();

    // Checks whether a given point lies on/in any segment of the sweepLineStatus
    bool pointOnSegment(RGPPoint2D p);
    bool pointInSegment(RGPPoint2D p);

    // Inserts/Removes a segment from the sweep line status when it's left/right half segment is encountered
    void insert(RGPSegment2D s);
    void remove(RGPSegment2D s);

    // Check if the dominant points of the given halfsegment and the next halfsegment (after the current index) of the indicated sequence are equal
    bool lookAheadF(RGPHalfSegment2D h);
    bool lookAheadG(RGPHalfSegment2D h);

private:
    // Pointers to the spatial object sequences
    const std::vector<F>& staticSequenceF;
    const std::vector<G>& staticSequenceG;
    std::vector<F> dynamicSequenceF;
    std::vector<G> dynamicSequenceG;

    // Static sequence sizes
    const int sizeF;
    const int sizeG;

    // Sequence index trackers
    int staticIndexF;
    int staticIndexG;
    int dynamicIndexF;
    int dynamicIndexG;

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

template<class F, class G>
inline
PlaneSweep<F,G>::PlaneSweep(const std::vector<F>& seqF, const std::vector<G>& seqG) : staticSequenceF(seqF), staticSequenceG(seqG), sizeF(seqF.size()), sizeG(seqG.size())
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
    staticIndexF = 0;
    staticIndexG = 0;

    if (!staticSequenceF.empty())
    {
        if (!staticSequenceG.empty())
        {
            if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG])
            {
                object = ObjectSelected::OBJ_F;
            }
            else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG])
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

template<>
inline
void PlaneSweep<RGPPoint2D,RGPHalfSegment2D>::select_first()
{
    staticIndexF = 0;
    staticIndexG = 0;

    if (!staticSequenceF.empty())
    {
        if (!staticSequenceG.empty())
        {
            if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG].dominantPoint)
            {
                object = ObjectSelected::OBJ_F;
            }
            else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG].dominantPoint)
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
        if (++staticIndexF < sizeF)
        {
            if (status != TraversalStatus::END_OF_G)
            {
                if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG])
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG])
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
        if (++staticIndexG < sizeG)
        {
            if (status != TraversalStatus::END_OF_F)
            {
                if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG])
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG])
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
        ++staticIndexF;
        ++staticIndexG;

        bool check_F = staticIndexF < sizeF;
        bool check_G = staticIndexG < sizeG;

        if (check_F && check_G)
        {
            if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG])
            {
                object = ObjectSelected::OBJ_F;
            }
            else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG])
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

template<>
inline
void PlaneSweep<RGPPoint2D,RGPHalfSegment2D>::select_next() {
    if (object == ObjectSelected::OBJ_F)
    {
        if (++staticIndexF < sizeF)
        {
            if (status != TraversalStatus::END_OF_G)
            {
                if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG].dominantPoint)
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG].dominantPoint)
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
        if (++staticIndexG < sizeG)
        {
            if (status != TraversalStatus::END_OF_F)
            {
                if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG].dominantPoint)
                {
                    object = ObjectSelected::OBJ_F;
                }
                else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG].dominantPoint)
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
        ++staticIndexF;
        ++staticIndexG;

        bool check_F = staticIndexF < sizeF;
        bool check_G = staticIndexG < sizeG;

        if (check_F && check_G)
        {
            if (staticSequenceF[staticIndexF] < staticSequenceG[staticIndexG].dominantPoint)
            {
                object = ObjectSelected::OBJ_F;
            }
            else if (staticSequenceF[staticIndexF] > staticSequenceG[staticIndexG].dominantPoint)
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

}

template <class F, class G>
inline
G PlaneSweep<F,G>::getEventG()
{

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

}

template <class F, class G>
inline
void PlaneSweep<F,G>::remove(RGPSegment2D s)
{

}

template <class F, class G>
inline
bool PlaneSweep<F,G>::lookAheadF(RGPHalfSegment2D h)
{

}

template <class F, class G>
inline
bool PlaneSweep<F,G>::lookAheadG(RGPHalfSegment2D h)
{

}

#endif //PLANESWEEP
