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

  return;
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
  // Status should always be at the end of none when function is called

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
      // Will end explore loop, does not need to change object
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
      // Will end explore loop, does not need to change object
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
      // Will end explore loop, does not need to change object
      status = TraversalStatus::END_OF_G;
    }
    else if (check_G)
    {
      // Will end explore loop, does not need to change object
      status = TraversalStatus::END_OF_F;
    }
    else
    {
      // Will end explore loop, does not need to change object
      status = TraversalStatus::END_OF_BOTH;
    }
  }
}

void PlaneSweep::select_next(Point2D  &spatialObj_F, Line2D    &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  // Status could be at the end of F or none when function is called
//
//  if (object == ObjectSelected::F)
//  {
//    if (++pointerF < spatialObj_F.getNumberOfPoints())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Guaranteed by the explore while loop to never be at the end of G if this function is called
//      object = ObjectSelected::G;
//      status = TraversalStatus::END_OF_F;
//    }
//  }
//  else if (object == ObjectSelected::G)
//  {
//    if (++pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (status != TraversalStatus::END_OF_F)
//      {
//        if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//        {
//          object = ObjectSelected::F;
//        }
//        else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//        {
//          object = ObjectSelected::G;
//        }
//        else
//        {
//          object = ObjectSelected::BOTH;
//        }
//      }
//      else
//      {
//        object = ObjectSelected::G;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (object == ObjectSelected::BOTH)
//  {
//    ++pointerF;
//    ++pointerG;
//
//    bool check_F = pointerF < spatialObj_F.getNumberOfPoints();
//    bool check_G = pointerG < spatialObj_G.getNumberOfSegments() * 2; // * 2 to indicate the number of half segments
//
//    if (check_F && check_G)
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else if (check_F)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//    else if (check_G)
//    {
//      object = ObjectSelected::G;
//      status = TraversalStatus::END_OF_F;
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_BOTH;
//    }
//  }
}

void PlaneSweep::select_next(Point2D  &spatialObj_F, Region2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  // Status should always be at the end of none when function is called
//
//  if (object == ObjectSelected::F)
//  {
//    if (++pointerF < spatialObj_F.getNumberOfPoints())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//  }
//  else if (object == ObjectSelected::G)
//  {
//    if (++pointerG < spatialObj_G.getNumberOfSegments * 2) // * 2 to indicate the number of half segments
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (object == ObjectSelected::BOTH)
//  {
//    ++pointerF;
//    ++pointerG;
//
//    bool check_F = pointerF < spatialObj_F.getNumberOfPoints();
//    bool check_G = pointerG < spatialObj_G.getNumberOfSegments * 2; // * 2 to indicate the number of half segments
//
//    if (check_F && check_G)
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else if (check_F)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//    else if (check_G)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_BOTH;
//    }
//  }
}

void PlaneSweep::select_next(Line2D &spatialObj_F, Line2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  // Status could be at the end of F, end of G or none when function is called
//
//  if (object == ObjectSelected::F)
//  {
//    if (++pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (status != TraversalStatus::END_OF_G)
//      {
//        if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::F;
//        }
//        else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::G;
//        }
//        else
//        {
//          object = ObjectSelected::BOTH;
//        }
//      }
//      else
//      {
//        object = ObjectSelected::F;
//      }
//    }
//    else
//    {
//      if (status == TraversalStatus::END_OF_G)
//      {
//        // Will end explore loop, does not need to change object
//        status == TraversalStatus::END_OF_BOTH;
//      }
//      else
//      {
//        object = ObjectSelected::G;
//        status = TraversalStatus::END_OF_F;
//      }
//    }
//  }
//  else if (object == ObjectSelected::G)
//  {
//    if (++pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (status != TraversalStatus::END_OF_F)
//      {
//        if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::F;
//        }
//        else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::G;
//        }
//        else
//        {
//          object = ObjectSelected::BOTH;
//        }
//      }
//      else
//      {
//        object = ObjectSelected::G;
//      }
//    }
//    else
//    {
//      if (status == TraversalStatus::END_OF_F)
//      {
//        // Will end explore loop, does not need to change object
//        status == TraversalStatus::END_OF_BOTH;
//      }
//      else
//      {
//        object = ObjectSelected::F;
//        status = TraversalStatus::END_OF_G;
//      }
//    }
//  }
//  else if (object == ObjectSelected::BOTH)
//  {
//    ++pointerF;
//    ++pointerG;
//
//    bool check_F = pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    bool check_G = pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//
//    if (check_F && check_G)
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else if (check_F)
//    {
//      object = ObjectSelected::F;
//      status = TraversalStatus::END_OF_G;
//    }
//    else if (check_G)
//    {
//      object = ObjectSelected::G;
//      status = TraversalStatus::END_OF_F;
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_BOTH;
//    }
//  }
}

void PlaneSweep::select_next(Line2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  // Status could be at the end of G or none when function is called
//
//  if (object == ObjectSelected::F)
//  {
//    if (++pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (status != TraversalStatus::END_OF_G)
//      {
//        if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::F;
//        }
//        else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//        {
//          object = ObjectSelected::G;
//        }
//        else
//        {
//          object = ObjectSelected::BOTH;
//        }
//      }
//      else
//      {
//        object = ObjectSelected::F;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//  }
//  else if (object == ObjectSelected::G)
//  {
//    if (++pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Guaranteed by the explore while loop to never be at the end of G if this function is called
//      object = ObjectSelected::F;
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (object == ObjectSelected::BOTH)
//  {
//    ++pointerF;
//    ++pointerG;
//
//    bool check_F = pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    bool check_G = pointerG < spatialObj_G.getNumberOfSegments() * 2; // * 2 to indicate the number of half segments
//
//    if (check_F && check_G)
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else if (check_F)
//    {
//      object = ObjectSelected::F;
//      status = TraversalStatus::END_OF_G;
//    }
//    else if (check_G)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_BOTH;
//    }
//  }
}

void PlaneSweep::select_next(Region2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  // Status should always be at the end of none when function is called
//
//  if (object == ObjectSelected::F)
//  {
//    if (++pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//  }
//  else if (object == ObjectSelected::G)
//  {
//    if (++pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (object == ObjectSelected::BOTH)
//  {
//    ++pointerF;
//    ++pointerG;
//
//    bool check_F = pointerF < spatialObj_F.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//    bool check_G = pointerG < spatialObj_G.getNumberOfSegments() * 2) // * 2 to indicate the number of half segments
//
//    if (check_F && check_G)
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//    }
//    else if (check_F)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_G;
//    }
//    else if (check_G)
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_F;
//    }
//    else
//    {
//      // Will end explore loop, does not need to change object
//      status = TraversalStatus::END_OF_BOTH;
//    }
//  }
}

// Select first
void PlaneSweep::select_first(Point2D  &spatialObj_F, Point2D   &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
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

void PlaneSweep::select_first(Point2D  &spatialObj_F, Line2D    &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  pointerF = 0;
//  pointerG = 0;
//
//  if (!spatialObj_F.isEmptyPoint())
//  {
//    if (!spatialObj_G.isEmptyLine())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//      status = TraversalStatus::END_OF_NONE;
//    }
//    else
//    {
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (!spatialObj_G.isEmptyLine())
//  {
//    status = TraversalStatus::END_OF_F;
//  }
//  else
//  {
//    status = TraversalStatus::END_OF_BOTH;
//  }
//
//  return;
}

void PlaneSweep::select_first(Point2D  &spatialObj_F, Region2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  pointerF = 0;
//  pointerG = 0;
//
//  if (!spatialObj_F.isEmptyPoint())
//  {
//    if (!spatialObj_G.isEmptyRegion())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG].dominantPoint)
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//      status = TraversalStatus::END_OF_NONE;
//    }
//    else
//    {
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (!spatialObj_G.isEmptyRegion())
//  {
//    status = TraversalStatus::END_OF_F;
//  }
//  else
//  {
//    status = TraversalStatus::END_OF_BOTH;
//  }
//
//  return;
}

void PlaneSweep::select_first(Line2D &spatialObj_F, Line2D &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  pointerF = 0;
//  pointerG = 0;
//
//  if (!spatialObj_F.isEmptyLine())
//  {
//    if (!spatialObj_G.isEmptyLine())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//      status = TraversalStatus::END_OF_NONE;
//    }
//    else
//    {
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (!spatialObj_G.isEmptyLine())
//  {
//    status = TraversalStatus::END_OF_F;
//  }
//  else
//  {
//    status = TraversalStatus::END_OF_BOTH;
//  }
//
//  return;
}

void PlaneSweep::select_first(Line2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  pointerF = 0;
//  pointerG = 0;
//
//  if (!spatialObj_F.isEmptyLine())
//  {
//    if (!spatialObj_G.isEmptyRegion())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//      status = TraversalStatus::END_OF_NONE;
//    }
//    else
//    {
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (!spatialObj_G.isEmptyRegion())
//  {
//    status = TraversalStatus::END_OF_F;
//  }
//  else
//  {
//    status = TraversalStatus::END_OF_BOTH;
//  }
//
//  return;
}

void PlaneSweep::select_first(Region2D &spatialObj_F, Region2D  &spatialObj_G, ObjectSelected &object, TraversalStatus &status)
{
//  pointerF = 0;
//  pointerG = 0;
//
//  if (!spatialObj_F.isEmptyRegion())
//  {
//    if (!spatialObj_G.isEmptyRegion())
//    {
//      if (spatialObj_F[pointerF] < spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::F;
//      }
//      else if (spatialObj_F[pointerF] > spatialObj_G[pointerG])
//      {
//        object = ObjectSelected::G;
//      }
//      else
//      {
//        object = ObjectSelected::BOTH;
//      }
//      status = TraversalStatus::END_OF_NONE;
//    }
//    else
//    {
//      status = TraversalStatus::END_OF_G;
//    }
//  }
//  else if (!spatialObj_G.isEmptyRegion())
//  {
//    status = TraversalStatus::END_OF_F;
//  }
//  else
//  {
//    status = TraversalStatus::END_OF_BOTH;
//  }
//
//  return;
}