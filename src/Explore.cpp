#include "../include/Explore.h"

// Point x Point
void Explore::explore(Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  PlaneSweep<RGPPoint2D,RGPPoint2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  sweep.select_first();

  // Terminates when the end of an object is reached, or all flags are turned on
  while (sweep.status == TraversalStatus::END_OF_NONE && !(featureVectorF[poi_disjoint] && featureVectorG[poi_disjoint] && featureVectorF[poi_shared]))
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
  }

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

// Point x Line
void Explore::explore(Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  PlaneSweep<RGPPoint2D,RGPHalfSegment2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  optional<RGPPoint2D> lastDominantPoint = nullopt; // Empty point

  sweep.select_first();

  while (sweep.status != TraversalStatus::END_OF_G && sweep.status != TraversalStatus::END_OF_BOTH &&
         !(featureVectorF[poi_disjoint] && featureVectorF[poi_on_interior] && featureVectorF[poi_on_bound] && featureVectorG[bound_poi_disjoint]))
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

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
      }

      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (lastDominantPoint != dp)
      {
        lastDominantPoint = dp;

        if (!sweep.lookAheadG(h))
        {
          featureVectorG[bound_poi_disjoint] = true;
        }
      }
    }
    else // BOTH
    {
      RGPHalfSegment2D h = sweep.getEventG();

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
      }

      lastDominantPoint = make_optional(h.dominantPoint);

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
  }

  if (sweep.status == TraversalStatus::END_OF_G)
  {
    featureVectorF[poi_disjoint] = true;
  }
}

// Point x Region
void Explore::explore(Point2DImpl  &spatialObj_F, Region2DImpl &spatialObj_G, std::vector<bool> &featureVectorF)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

  PlaneSweep<RGPPoint2D,RGPAnnotatedHalfSegment2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  sweep.select_first();

  while (sweep.status == TraversalStatus::END_OF_NONE && !(featureVectorF[poi_inside] && featureVectorF[poi_on_bound] && featureVectorF[poi_outside]))
  {
    if (sweep.object == ObjectSelected::OBJ_F)
    {
      RGPPoint2D p = sweep.getEventF();

      if (sweep.pointOnSegment(p))
      {
        featureVectorF[poi_on_bound] = true;
      }
      else
      {
        if (auto ah = sweep.getAnnotatedHalfSegmentBelowPoint(p))
        {
          if (ah->interiorIsAbove)
          {
            featureVectorF[poi_inside] = true;
          }
          else
          {
            featureVectorF[poi_outside] = true;
          }
        }
        else
        {
          featureVectorF[poi_outside] = true;
        }
      }
    }
    else
    {
      RGPAnnotatedHalfSegment2D ah = sweep.getEventG();

      if (ah.dominantPoint == ah.segment.point1) // Left halfsegment
      {
        sweep.insert(ah.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(ah.segment);
      }

      if (sweep.object == ObjectSelected::BOTH)
      {
        featureVectorF[poi_on_bound] = true;
      }
    }

    sweep.select_next();
  }

  if (sweep.status == TraversalStatus::END_OF_G)
  {
    featureVectorF[poi_outside] = true;
  }
}

// Line x Line
void Explore::explore(Line2DImpl &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  PlaneSweep<RGPHalfSegment2D,RGPHalfSegment2D> sweep(spatialObj_F.getSequence(), spatialObj_G.getSequence());

  optional<RGPPoint2D> lastDominantPointF = nullopt;
  optional<RGPPoint2D> lastDominantPointG = nullopt;
  optional<RGPPoint2D> lastBoundaryPointF = nullopt;
  optional<RGPPoint2D> lastBoundaryPointG = nullopt;

  sweep.select_first();

  while (sweep.status != TraversalStatus::END_OF_BOTH &&
         !(featureVectorF[seg_shared] && featureVectorF[interior_poi_shared] && featureVectorF[seg_unshared] &&
           featureVectorF[bound_on_interior] && featureVectorF[bound_shared] && featureVectorF[bound_disjoint] &&
           featureVectorG[bound_disjoint] && featureVectorG[bound_on_interior] && featureVectorG[seg_unshared]))
  {
    if (sweep.object == ObjectSelected::OBJ_F)
    {
      RGPHalfSegment2D h = sweep.getEventF();

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
        featureVectorF[seg_unshared] = true;
      }

      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (lastDominantPointF != dp)
      {
        lastDominantPointF = dp;

        if (!sweep.lookAheadF(h))
        {
          lastBoundaryPointF = dp;

          if (lastBoundaryPointF == lastBoundaryPointG)
          {
            featureVectorF[bound_shared] = true;
          }
          else if (lastBoundaryPointF == lastDominantPointG)
          {
            featureVectorF[bound_on_interior] = true;
          }
          else if(!sweep.lookAheadG(h))
          {
            featureVectorF[bound_disjoint] = true;
          }
        }
      }

      if (dp != lastBoundaryPointF)
      {
        if (dp == lastBoundaryPointG)
        {
          featureVectorG[bound_on_interior] = true;
        }
        else if (dp == lastDominantPointG)
        {
          featureVectorF[interior_poi_shared] = true;
        }
      }
    }
    else if (sweep.object == ObjectSelected::OBJ_G)
    {
      RGPHalfSegment2D h = sweep.getEventG();

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
        featureVectorG[seg_unshared] = true;
      }

      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (lastDominantPointG != dp)
      {
        lastDominantPointG = dp;

        if (!sweep.lookAheadG(h))
        {
          lastBoundaryPointG = dp;

          if (lastBoundaryPointG == lastBoundaryPointF)
          {
            featureVectorG[bound_shared] = true;
          }
          else if (lastBoundaryPointG == lastDominantPointF)
          {
            featureVectorG[bound_on_interior] = true;
          }
          else if(!sweep.lookAheadF(h))
          {
            featureVectorG[bound_disjoint] = true;
          }
        }
      }

      if (dp != lastBoundaryPointG)
      {
        if (dp == lastBoundaryPointF)
        {
          featureVectorF[bound_on_interior] = true;
        }
        else if (dp == lastDominantPointF)
        {
          featureVectorG[interior_poi_shared] = true;
        }
      }
    }
    else // BOTH
    {
      RGPHalfSegment2D h = sweep.getEventF();
      featureVectorF[seg_shared] = true;

      if (h.dominantPoint == h.segment.point1) // Left halfsegment
      {
        sweep.insert(h.segment);
      }
      else // Right halfsegment
      {
        sweep.remove(h.segment);
      }

      optional<RGPPoint2D> dp = make_optional(h.dominantPoint);

      if (lastDominantPointF != dp)
      {
        lastDominantPointF = dp;

        if (!sweep.lookAheadF(h))
        {
          lastBoundaryPointF = dp;
        }
      }

      if (dp != lastDominantPointG)
      {
        lastDominantPointG = dp;

        if (!sweep.lookAheadG(h))
        {
          lastBoundaryPointG = dp;
        }
      }

      if (lastBoundaryPointF == lastBoundaryPointG)
      {
        featureVectorF[bound_shared] = true;
      }
      else
      {
        if (lastBoundaryPointF == lastDominantPointG)
        {
          featureVectorF[bound_on_interior] = true;
        }

        if (lastBoundaryPointG == lastDominantPointF)
        {
          featureVectorG[bound_on_interior] = true;
        }
      }
    }

    if (sweep.status == TraversalStatus::END_OF_F)
    {
      featureVectorG[seg_unshared] = true;
    }
    else if (sweep.status == TraversalStatus::END_OF_G)
    {
      featureVectorF[seg_unshared] = true;
    }

    sweep.select_next();
  }
}

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
