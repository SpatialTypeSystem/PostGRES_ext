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
	// A0B-
	if ( featureVectorF[poi_disjoint] ) { // vf[poi_disjoint]
		// A0B0, moved right
		if ( featureVectorF[poi_shared] ) { // vf[poi_shared]
			// A-B0
			if ( featureVectorG[poi_disjoint] ) { // vg[poi_disjoint]
				// 5
				return overlap;
			} else {
				// 4
				return contains;
			}
		} else {
			// 1
			return disjoint;
		}
	} else {
		// A-B0, moved left
		if ( featureVectorG[poi_disjoint] ) { // vg[poi_disjoint]
			// 3
			return inside;
		} else {
			// 2
			return equal;
		}

	}
	return disjoint;
}

PREDICATE Evaluate::determine( Point2DImpl  &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// To do
	return disjoint;
}

PREDICATE Evaluate::determine( Point2DImpl  &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG)
{
	// To do
	return disjoint;
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
