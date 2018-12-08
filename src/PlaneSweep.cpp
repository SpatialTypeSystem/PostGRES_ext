#include "../include/PlaneSweep.h"

//Constructors
template<class F, class G>
PlaneSweep<F,G>::PlaneSweep(typename std::vector<F>::iterator startIteratorF, typename std::vector<F>::iterator endIteratorF,
  typename std::vector<G>::iterator startIteratorG, typename std::vector<G>::iterator endIteratorG) :
	staticIteratorF(startIteratorF), endStaticIteratorF(endIteratorF), staticIteratorG(startIteratorG), endStaticIteratorG(endIteratorG)
{
    object = ObjectSelected::NONE;
    status = TraversalStatus::END_OF_NONE;
}

template<class F, class G>
PlaneSweep<F,G>::~PlaneSweep()
{
  //Empty
}

template<class F, class G>
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

template<class F, class G>
F PlaneSweep<F,G>::getEventF()
{
    // Get event returns the element to which the logical pointer of a
    // point or half segment sequence of an object points to
    return *staticIteratorF;
}

template<class F, class G>
G PlaneSweep<F,G>::getEventG()
{
    // Get event returns the element to which the logical pointer of a
    // point or half segment sequence of an object points to
    return *staticIteratorG;
}

template<class F, class G>
bool PlaneSweep<F,G>::pointOnSegment(RGPPoint2D p)
{
  // Checks whether a given point lies on/in any segment of the sweep line status

}

template<class F, class G>
bool PlaneSweep<F,G>::pointInSegment(RGPPoint2D p)
{
  // Checks whether a given point lies on/in any segment of the sweep line status


}

template<class F, class G>
// Inserts/Removes a segment from the sweep line status when
// it's left/right half segment is encountered
void PlaneSweep<F,G>::insert(RGPSegment2D s)
{
    sweepLineStatus.insert(s);
}


template<class F, class G>
void PlaneSweep<F,G>::remove(RGPSegment2D s)
{
    sweepLineStatus.deleteKey(s);
}

template<class F, class G>
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

template<class F, class G>
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


template<class F, class G>
optional<bool> PlaneSweep<F,G>::getAttributeOfSegmentBelow(RGPPoint2D p)
{
    // Returns the nearest annotated halfsegment, from the sweep line status,
    // below a given point, if there is one

    // Loops through sweep line status, checking if the segment is classified as less than our RGPPoint2D
    // Returns the first one that is true

}

template<class F, class G>
optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOfPredecessor(RGPSegment2D s)
{
    // Returns the overlap numbers of the predecessor to the given segment in the sweep line status

}

template<class F, class G>
optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOf(RGPSegment2D s)
{
    // Returns the overlap numbers of the given segment in the sweep line status
}
