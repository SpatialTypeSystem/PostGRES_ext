#include "../include/Explore.h"

// Point x Point
void Explore::explore(Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  PlaneSweep<RGPPoint2D,RGPPoint2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  sweep.select_first();

  do
  {
    if (sweep.object == ObjectSelected::OBJ_F)
    {
      featureVectorF[poi_disjoint] = true;
    }
    else if (sweep.object == ObjectSelected::OBJ_G)
    {
      featureVectorG[poi_disjoint] = true;
    }
    else if (sweep.object == ObjectSelected::BOTH)
    {
      featureVectorF[poi_shared] = true;
    }

    sweep.select_next();
  } while (sweep.status == TraversalStatus::END_OF_NONE &&
      !featureVectorF[poi_disjoint] &&
      featureVectorG[poi_disjoint] &&
      featureVectorF[poi_shared]);

  if (sweep.status == TraversalStatus::END_OF_F)
  {
    featureVectorG[poi_disjoint] = true;
  }
  else if (sweep.status == TraversalStatus::END_OF_G)
  {
    featureVectorF[poi_disjoint] = true;
  }

  return;
}

//// Point x Line
void Explore::explore(Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  PlaneSweep<RGPPoint2D,RGPHalfSegment2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  optional<RGPPoint2D> lastDominantPoint = nullopt; // Empty point

  sweep.select_first();

  do
  {
    if (sweep.object == ObjectSelected::OBJ_F)
    {
      RGPPoint2D p = sweep.getEventF();

      if (sweep.pointInSegment(p))
      {
        featureVectorF[poi_on_interior] = true;
      }
      else
      {
        featureVectorF[poi_disjoint] = true;
      }
    }
    else if (sweep.object == ObjectSelected::OBJ_G)
    {
      RGPHalfSegment2D h = sweep.getEventG();
      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
      }

      if (lastDominantPoint != dp)
      {
        lastDominantPoint = dp;

        if (!sweep.lookAheadG(h))
        {
          featureVectorG[bound_poi_disjoint] = true;
        }
      }
    }
    else if (sweep.object == ObjectSelected::BOTH)
    {
      RGPHalfSegment2D h = sweep.getEventG();
      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
      }

      lastDominantPoint = dp;

      if (sweep.lookAheadG(h))
      {
        featureVectorF[poi_on_interior] = true;
      }
      else
      {
        featureVectorF[poi_on_bound] = true;
      }
    }

    sweep.select_next();
  } while (sweep.status != TraversalStatus::END_OF_G &&
      sweep.status != TraversalStatus::END_OF_BOTH &&
      !featureVectorF[poi_disjoint] &&
      featureVectorF[poi_on_interior] &&
      featureVectorF[poi_on_bound] &&
      featureVectorG[bound_poi_disjoint]);
}

//// Point x Region
//void Explore::explore(Point2D  &spatialObj_F, Region2D &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//
//}
//
//// Line x Line
//void Explore::explore(Line2D &spatialObj_F, Line2D &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//
//}
//
//// Line x Region
//void Explore::explore(Line2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//
//}
//
//// Region x Region
//void Explore::explore(Region2D &spatialObj_F, Region2D  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//
//}
