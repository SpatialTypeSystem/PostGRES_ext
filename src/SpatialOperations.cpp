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

Point2D union(Point2D F, Point2D G) {
	return new Point2D();
}
Line2D union(Line2D F, Line2D G) {
	return new Line2D();
}

Region2D union(Region2D F, Region2D G) {
	return new Region2D();
}

Point2D intersection(Point2D F, Point2D G) {
	return new Point2D();
}

Line2D intersection(Line2D F, Line2D G) {
	return new Line2D();
}

Region2D intersection(Region2D F, Region2D G) {
	return new Region2D();
}

Line2D intersection(Region2D F, Line2D G) {
	return new Line2D();
}

Point2D difference(Point2D F, Point2D G) {
	return new Point2D();
}

Line2D difference(Line2D F, Line2D G) {
	return new Line2D();
}

Region2D difference(Region2D F, Region2D G) {
	return new Region2D();
}
