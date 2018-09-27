#ifndef REGION2D_H
#define REGION2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Region2D{

private:
	// Fields
	Region2DImplStruct implStruct;

public:
	// Constructors
	Region2D(); //Empty constructor
	Region2D(std::vector<std::vector<RGPSegment2D>> listOfRegions);
	Region2D(string listOfRegion2DString);
	Region2D(ifstream& file); // Send in file for constructor (possibly .txt)
	~Region2D();

	// Methods
	string getRegionString(); // Get the region as human readable ASCII string
	Number area();
        static bool isValidRegion(Region2D region);
	int getNumberOfFaces();
	vector<RGPSegment2D> getBoundingBox();
	// bool update(const iterator, vector<RGPSegment2D>);
	bool addFace(vector<RGPSegment2D>);
	// bool removeFace(const iterator);
	bool operator==(const Region2D &p2d);
	bool operator!=(const Region2D &p2d);
};

#endif // REGION2D_H
