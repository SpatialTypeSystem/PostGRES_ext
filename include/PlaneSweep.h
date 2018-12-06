#ifndef PLANESWEEP_H
#define PLANESWEEP_H

#include "RGP.h"
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

    ObjectSelected object;
    TraversalStatus status;

    PlaneSweep(const std::vector<F>& seqF, const std::vector<G>& seqG);
    ~PlaneSweep();

    void select_first();
    void select_next();

    // Get event returns the element to which the logical pointer of a point or half segment sequence of an object points to
    typename std::vector<F>::const_iterator getEventF();
    typename std::vector<G>::const_iterator getEventG();

    // Checks whether a given point lies on/in any segment of the sweep line status
    bool pointOnSegment(RGPPoint2D p);
    bool pointInSegment(RGPPoint2D p);

    // Inserts/Removes a segment from the sweep line status when it's left/right half segment is encountered
    void insert(RGPSegment2D s);
    void remove(RGPSegment2D s);

    // Check if the dominant points of the given halfsegment and the next halfsegment (after the current index) of the indicated sequence are equal
    bool lookAheadF(RGPHalfSegment2D h);
    bool lookAheadG(RGPHalfSegment2D h);

    int staticIndexF, staticIndexG;
    int sizeF, sizeG =0;


    optional<bool> getAttributeOfSegmentBelow(RGPPoint2D p); // Returns the nearest annotated halfsegment, from the sweep line status, below a given point, if there is one
    optional<std::tuple<short, short>> getOverlapNumbersOfPredecessor(RGPSegment2D s); // Returns the overlap numbers of the predecessor to the given segment in the sweep line status
    optional<std::tuple<short, short>> getOverlapNumbersOf(RGPSegment2D s); // Returns the overlap numbers of the given segment in the sweep line status

private:

    // References to the spatial object sequences
    const std::vector<F>& staticSequenceF;
    const std::vector<G>& staticSequenceG;
    std::vector<F> dynamicSequenceF;
    std::vector<G> dynamicSequenceG;
    typename std::vector<F>::iterator staticIteratorF;
    typename std::vector<G>::iterator staticIteratorG;
    typename std::vector<F>::iterator dynamicIteratorF;
    typename std::vector<G>::iterator dynamicIteratorG;

    //// NON-TEMPLATED CODE ////

//    std::queue<RGPPoint2D> eventPointSchedule;  // Stores event points
//
//    struct SweepLineStatus; //Holds the state of the intersection of the sweep line
//
//    void set_attr(SweepLineStatus &sweepLineStatus, bool attribute);  //Sets an attribute for a segment in the sweep line status
//    bool get_attr(SweepLineStatus &sweepLineStatus);	//Gets an attribute from a segment in the sweep line status
//    bool get_pred_attr(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Yields the attribute from the prdecessor of a segment in the sweepline status
//    bool pred_exists(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Checks for a segment in the sweepLineStatus to check if it hasa predecessor
//    bool common_point_exists(SweepLineStatus &sweepLineStatus, RGPHalfSegment2D segment); //Checks for a neighbor segment
//    bool current_exists(SweepLineStatus &sweepLineStatus); //Tests whether such a segment exists


};


// Methods

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

template<>
inline
void PlaneSweep<RGPPoint2D,RGPAnnotatedHalfSegment2D>::select_first()
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

template<>
inline
void PlaneSweep<RGPPoint2D,RGPAnnotatedHalfSegment2D>::select_next() {
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

// template <class F, class G>
// inline
// //start implemnting iterators
// F PlaneSweep<F,G>::getEventF()
// {
//
//
// }
//
// template <class F, class G>
// inline
// G PlaneSweep<F,G>::getEventG()
// {
//
// }
//
// template <class F, class G>
// inline
// bool PlaneSweep<F,G>::pointOnSegment(RGPPoint2D p)
// {
//
// }
//
// template <class F, class G>
// inline
// bool PlaneSweep<F,G>::pointInSegment(RGPPoint2D p)
// {
//
// }
//
// template <class F, class G>
// inline
// void PlaneSweep<F,G>::insert(RGPSegment2D s)
// {
//
// }
//
// template <class F, class G>
// inline
// void PlaneSweep<F,G>::remove(RGPSegment2D s)
// {
//
// }
//
// template <class F, class G>
// inline
// bool PlaneSweep<F,G>::lookAheadF(RGPHalfSegment2D h)
// {
//
// }
//
// template <class F, class G>
// inline
// bool PlaneSweep<F,G>::lookAheadG(RGPHalfSegment2D h)
// {
//
// }
//
// template <class F, class G>
// inline
// optional<bool> PlaneSweep<F,G>::getAttributeOfSegmentBelow(RGPPoint2D p)
// {
//
// }
//
// template <class F, class G>
// inline
// optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOfPredecessor(RGPSegment2D s)
// {
//
// }
//
// template <class F, class G>
// inline
// optional<std::tuple<short, short>> PlaneSweep<F,G>::getOverlapNumbersOf(RGPSegment2D s)
// {

// }
#endif //PLANESWEEP
