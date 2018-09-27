#ifndef POINT2D_H
#define POINT2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Point2D{
private:
	// Fields
	Line2DImplStruct implStruct;

public:
	// Constructors
	Point2D();
	Point2D(std::vector<RGPPoint2D> listOfPoints);
	Point2D(ifstream& file);
	Point2D(string listOfPoint2DString);
	~Point2D();

	// Methods
	string getPointString();  // Get the point as human readable ASCII string
	static bool isValidPoint();
	bool operator==(const Point2D &p2d);
	bool operator!=(const Point2D &p2d);
	int getNumberPoints();
	vector<RGPSegment2D> getBoundingBox();
	// bool update(const iterator iter, RGPPoint2D rgpp);
	bool add(RGPPoint2D rgpp2d);
	// bool remove(const iterator iter);

};

#endif //POINT2D_H
