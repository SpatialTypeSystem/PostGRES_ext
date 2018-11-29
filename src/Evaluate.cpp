#include "Evaluate.h"

Evaluate::Evaluate() {}

Evaluate::~Evaluate() {}

// ------------ Validate -----------------

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

bool Evaluate::validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate)
{
	if( Evaluate::determine(spatialObj_F, spatialObj_G, featureVectorF, featureVectorG) == predicate ) { return true; } else { return false; }
}

// ------------ Determine -----------------

PREDICATE Evaluate::determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {poi_shared, poi_disjoint};

	if ( featureVectorF[poi_disjoint] ) { // A0B-
		if ( featureVectorF[poi_shared] ) { // A0B0, moved right
			if ( featureVectorG[poi_disjoint] ) { // A-B0
				return overlap; // 5
			} else {
				return contains; // 4
			}
		} else {
			return disjoint; // 1
		}
	} else { // A-B0, moved left
		if ( featureVectorG[poi_disjoint] ) { // vg[poi_disjoint]
			return inside; // 3
		} else {
			return equal; // 2
		}

	}
}

PREDICATE Evaluate::determine( Point2DImpl  &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

	if( featureVectorF[poi_on_interior] ) { // A0B0
		if( featureVectorF[poi_on_bound] ) { // A0&B (boundary B) 
			if( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return overlap; // 14
				} else {
					return overlap; //13
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return inside; // 12
				} else {
					return inside; // 11
				}
			}
		} else {
			if (  featureVectorF[poi_disjoint]) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return overlap; // 9
				} else {
					return overlap; // 10
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return inside; // 7
				} else {
					return inside; // 8
				}
			}
		}
	} else {
		if( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return meet; // 6
				} else {
					return meet; // 5
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return meet; // 4
				} else {
					return meet; // 3
				}
			}
		} else { // A-&B
			if ( featureVectorG[bound_poi_disjoint] ) {
				return disjoint; // 2
			} else {
				return disjoint; // 1
			}
		}
	}
}

PREDICATE Evaluate::determine( Point2DImpl  &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
	enum VectorFlag {poi_inside, poi_on_bound, poi_outside};
	
	if ( featureVectorF[poi_inside] ) { // A0B0
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { // A0B-
				return overlap; // 7
			} else {
				return inside; // 6
			}
		} else {
			if ( featureVectorF[poi_outside] ) { // A0B-
				return inside; // 4
			} else {
				return overlap; // 5
			}
		}
	} else {
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { //A0B-
				return meet; // 3
			} else {
				return meet; // 2
			}
		} else {
			return disjoint; // 1
		}
	}
}

PREDICATE Evaluate::determine( Line2DImpl   &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// To do
	return disjoint;
}

PREDICATE Evaluate::determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// To do
	return disjoint;
}

PREDICATE Evaluate::determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// To do
	return disjoint;
}
