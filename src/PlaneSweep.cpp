#include "PlaneSweep.h"

template<class F, class G>
PlaneSweep<F,G>::PlaneSweep(std::vector<F>* seqF, std::vector<G>* seqG) : sequenceF(seqF), sequenceG(seqG), sizeF(seqF->size()), sizeG(seqG->size())
{
  object = ObjectSelected::NONE;
  status = TraversalStatus::END_OF_NONE;
}

template<class F, class G>
PlaneSweep<F,G>::~PlaneSweep()
{

}

template<class F, class G>
void PlaneSweep<F,G>::select_first()
{
  indexF = 0;
  indexG = 0;

  if (!sequenceF->empty())
  {
    if (!sequenceG->empty())
    {
      if (*sequenceF[indexF] < *sequenceG[indexG])
      {
        object = ObjectSelected::OBJ_F;
      }
      else if (*sequenceF[indexF] > *sequenceG[indexG])
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
  else if (!sequenceG->empty())
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
    if (++indexF < sizeF)
    {
      if (status != TraversalStatus::END_OF_G)
      {
        if (*sequenceF[indexF] < *sequenceG[indexG])
        {
          object = ObjectSelected::OBJ_F;
        }
        else if (*sequenceF[indexF] > *sequenceG[indexG])
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
        status == TraversalStatus::END_OF_BOTH;
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
    if (++indexG < sizeG)
    {
      if (status != TraversalStatus::END_OF_F)
      {
        if (*sequenceF[indexF] < *sequenceG[indexG])
        {
          object = ObjectSelected::OBJ_F;
        }
        else if (*sequenceF[indexF] > *sequenceG[indexG])
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
    ++indexF;
    ++indexG;

    bool check_F = indexF < sizeF;
    bool check_G = indexG < sizeG;

    if (check_F && check_G)
    {
      if (*sequenceF[indexF] < *sequenceG[indexG])
      {
        object = ObjectSelected::OBJ_F;
      }
      else if (*sequenceF[indexF] > *sequenceG[indexG])
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