#ifndef REGION2D_H
#define REGION2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

struct Region2DImplStruct;

class Region2D{

private:
	// Fields
	Region2DImplStruct *implStruct;

public:
	// Constructors
	Region2D(); //Empty constructor
	Region2D(std::vector<std::vector<RGPSegment2D>> listOfRegions);
	Region2D(std::string listOfRegion2DString);
	Region2D(std::ifstream& file); // Send in file for constructor (possibly .txt)
	~Region2D();

	// Methods
	std::string getRegionString(); // Get the region as human readable ASCII string
	Number area();
        static bool isValidRegion(Region2D region);
	int getNumberOfFaces();
	std::vector<RGPSegment2D> getBoundingBox();
	bool addFace(std::vector<RGPSegment2D>);
	template <class T> bool update(T it, std::vector<RGPSegment2D>);
	template <class T> bool remove(T it);
	bool operator==(const Region2D &p2d);
	bool operator!=(const Region2D &p2d);
};

#endif // REGION2D_H
