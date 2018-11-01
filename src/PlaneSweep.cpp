#include "../include/PlaneSweep.h"

PlaneSweep::PlaneSweep()
{

}

PlaneSweep::~PlaneSweep()
{

}

// Point x Point
void PlaneSweep::explore(Point2D  &spatialObj_F, Point2D   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  ObjectSelected object = ObjectSelected::NONE;
  TraversalStatus status = TraversalStatus::END_OF_NONE;

  select_first(spatialObj_F, spatialObj_G, object, status);

  while (status == TraversalStatus::END_OF_NONE && !featureVectorF[poi_disjoint] && featureVectorG[poi_disjoint] && featureVectorF[poi_shared])
  {
    if (object == ObjectSelected::F)
    {
      featureVectorF[poi_disjoint] = true;
    }
    else if (object == ObjectSelected::G)
    {
      featureVectorG[poi_disjoint] = true;
    }
    else // object == both
    {
      featureVectorF[poi_shared] = true;
    }

    select_next(spatialObj_F, spatialObj_G, object, status);
  }

  if (status == TraversalStatus::END_OF_F)
  {
    featureVectorG[poi_disjoint] = true;
  }
  else if (status == TraversalStatus::END_OF_G)
  {
    featureVectorF[poi_disjoint] = true;
  }
}

// Point x Line
void PlaneSweep::explore(Point2D  &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Point x Region
void PlaneSweep::explore(Point2D  &spatialObj_F, Region2D &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Line x Line
void PlaneSweep::explore(Line2D &spatialObj_F, Line2D &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Line x Region
void PlaneSweep::explore(Line2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Region x Region
void PlaneSweep::explore(Region2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{

}

// Select Next
void PlaneSweep::select_next(Point2D  &spatialObj_F, Point2D   &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
  if (object == ObjectSelected::F)
  {
    if (++pointerF < spatialObj_F.getNumberOfPoints())
    {
      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
      {
        object = ObjectSelected::F;
      }
      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
      {
        object = ObjectSelected::G;
      }
      else
      {
        object = ObjectSelected::BOTH;
      }
    }
    else
    {
      status = TraversalStatus::END_OF_F;
    }
  }
  else if (object == ObjectSelected::G)
  {
    if (++pointerG < spatialObj_G.getNumberOfPoints())
    {
      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
      {
        object = ObjectSelected::F;
      }
      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
      {
        object = ObjectSelected::G;
      }
      else
      {
        object = ObjectSelected::BOTH;
      }
    }
    else
    {
      status = TraversalStatus::END_OF_G;
    }
  }
  else if (object == ObjectSelected::BOTH)
  {
    ++pointerF;
    ++pointerG;

    bool check_F = pointerF < spatialObj_F.getNumberOfPoints();
    bool check_G = pointerG < spatialObj_G.getNumberOfPoints();

    if (check_F && check_G)
    {
      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
      {
        object = ObjectSelected::F;
      }
      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
      {
        object = ObjectSelected::G;
      }
      else
      {
        object = ObjectSelected::BOTH;
      }
    }
    else if (check_F)
    {
      status = TraversalStatus::END_OF_G;
    }
    else if (check_G)
    {
      status = TraversalStatus::END_OF_F;
    }
    else
    {
      status = TraversalStatus::END_OF_BOTH;
    }
  }
}

void PlaneSweep::select_next(Point2D  &spatialObj_F, Line2D    &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_next(Point2D  &spatialObj_F, Region2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_next(Line2D &spatialObj_F, Line2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_next(Line2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_next(Region2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{

}

// Select first
void PlaneSweep::select_first(Point2D  &spatialObj_F, Point2D   &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{
  pointerF = 0;
  pointerG = 0;

  if (!spatialObj_F.isEmptyPoint())
  {
    if (!spatialObj_G.isEmptyPoint())
    {
      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
      {
        object = ObjectSelected::F;
      }
      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
      {
        object = ObjectSelected::G;
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
  else if (!spatialObj_G.isEmptyPoint())
  {
    status = TraversalStatus::END_OF_F;
  }
  else
  {
    status = TraversalStatus::END_OF_BOTH;
  }

  return;
}

void PlaneSweep::select_first(Point2D  &spatialObj_F, Line2D    &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_first(Point2D  &spatialObj_F, Region2D &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_first(Line2D &spatialObj_F, Line2D &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_first(Line2D &spatialObj_F, Region2D  &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{

}

void PlaneSweep::select_first(Region2D &spatialObj_F, Region2D  &spatialObj_G,ObjectSelected &object, TraversalStatus &status)
{

}