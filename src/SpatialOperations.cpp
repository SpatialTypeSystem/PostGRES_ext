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

Line2D SpatialOperations::union(Line2D F, Line2D G){
  Line2D line = new Line2D();
  // Add lines from F and G to new line object
  for (int i = 0; i < F.getNumberOfSegments(); i++){
    line.add( F[i] );
  }
  for (int i = 0; i < G.getNumberOfSegments(); i++){
    line.add( G[i] );
  }
  return line;
}

Region2D SpatialOperations::union(Region2D F, Region2D G){
  Region2D region = new Region2D();
  // Add regions from F and G to new region object
  for (int i = 0; i < F.getNumberOfFaces(); i++){
    region.add( F[i] );
  }
  for (int i = 0; i < G.getNumberOfFaces(); i++){
    region.add( G[i] );
  }
  return region;
}

Point2D SpatialOperations::intersection(Point2D F, Point2D G){
  Point2D poi = new Point2D();
  // Compare all points in F with all points in G
  // Add to new point object if points are the same
  for (int i = 0; i < F.getNumberOfPoints(); i++){
    for (int j = 0; j < G.getNumberOfPoints(); j++){
      if(F[i] == G[j]){
        poi.add( F[i] );
      }
    }
  }
  return poi;
}

Point2D SpatialOperations::difference(Point2D F, Point2D G){
  Point2D poi = new Point2D();
  // Add all points from F into new point object
  // Remove all points from G from new point object
  for (int i = 0; i < F.getNumberOfPoints(); i++){
		poi.add( F[i] );
	}
  for (int i = 0; i < G.getNumberOfPoints(); i++){
		poi.remove( G[i] );
	}
  return poi;
}

Point2D union(Point2D F, Point2D G) {
  //implemented
	return new Point2D();
}

Line2D union(Line2D F, Line2D G) {
  //implemented
	return new Line2D();
}

Region2D union(Region2D F, Region2D G) {
  //implemented
	return new Region2D();
}

Point2D intersection(Point2D F, Point2D G) {
  //implemented
	return new Point2D();
}

Line2D intersection(Line2D F, Line2D G) {
	return new Line2D();
}

/*Line2D intersection(Line2D F, Line2D G) {
	return new Point2D();
}*/

Region2D intersection(Region2D F, Region2D G) {
	return new Region2D();
}

Line2D intersection(Region2D F, Line2D G) {
	return new Line2D();
}

Point2D difference(Point2D F, Point2D G) {
  //implemented
	return new Point2D();
}

Line2D difference(Line2D F, Line2D G) {
	return new Line2D();
}

Region2D difference(Region2D F, Region2D G) {
	return new Region2D();
}
