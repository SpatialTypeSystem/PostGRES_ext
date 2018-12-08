#include "SpatialOperations.h"

SpatialOperations::SpatialOperations()
{
	// Emtpy
}

SpatialOperations::~SpatialOperations()
{
	// Emtpy
}

Point2D SpatialOperations::union(Point2D F, Point2D G) {
	Point2D poi = new Point2D();
	// Point2D won't accept duplicate points being added
	// Loop through both sets of points and add them to a new point object
	for (int i = 0; i < F.getNumberOfPoints(); i++ ) {
		poi.add( F[i] );
	}
	
	for (int i = 0; i < G.getNumberOfPoints(); i++ ) {
		poi.add( G[i] );
	}
	
	return poi;
}