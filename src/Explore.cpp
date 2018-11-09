#include "Explore.h"

//// Point x Point
//void Explore::explore(Point2D  &spatialObj_F, Point2D   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//  // Indicates what index in the bool vector represents what flag
//  enum VectorFlag {poi_shared, poi_disjoint};
//
//  ObjectSelected object = ObjectSelected::NONE;
//  TraversalStatus status = TraversalStatus::END_OF_NONE;
//
//  select_first(spatialObj_F, spatialObj_G, object, status);
//
//  while (status == TraversalStatus::END_OF_NONE &&
//      !featureVectorF[poi_disjoint] &&
//      featureVectorG[poi_disjoint] &&
//      featureVectorF[poi_shared])
//  {
//    if (object == ObjectSelected::F)
//    {
//      featureVectorF[poi_disjoint] = true;
//    }
//    else if (object == ObjectSelected::G)
//    {
//      featureVectorG[poi_disjoint] = true;
//    }
//    else // object == both
//    {
//      featureVectorF[poi_shared] = true;
//    }
//
//    select_next(spatialObj_F, spatialObj_G, object, status);
//  }
//
//  if (status == TraversalStatus::END_OF_F)
//  {
//    featureVectorG[poi_disjoint] = true;
//  }
//  else if (status == TraversalStatus::END_OF_G)
//  {
//    featureVectorF[poi_disjoint] = true;
//  }
//
//  return;
//}
//
//// Point x Line
//void Explore::explore(Point2D  &spatialObj_F, Line2D    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
//{
//  // Indicates what index in the bool vector represents what flag
//  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};
//
//  ObjectSelected object = ObjectSelected::NONE;
//  TraversalStatus status = TraversalStatus::END_OF_NONE;
//
//  new_sweep();
//  optional<RGPPoint2D> last_dp;
//
//  select_first(spatialObj_F, spatialObj_G, object, status);
//
//  while (status != TraversalStatus::END_OF_G &&
//      status != TraversalStatus::END_OF_BOTH &&
//      !featureVectorF[poi_disjoint] &&
//      featureVectorF[poi_on_interior] &&
//      featureVectorF[poi_on_bound] &&
//      featureVectorG[bound_poi_disjoint])
//  {
//    if (object == ObjectSelected::F)
//    {
//      RGPPoint2D p = get_event(F);
//
//      if ()
//    }
//  }
//}
//
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
