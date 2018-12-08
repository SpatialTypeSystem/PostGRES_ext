#ifndef REGION2D_H
#define REGION2D_H

#include "Number.h"
#include "RGP.h"
#include <string>
#include <vector>

class Region2D
{
public:
	// Constructors
	Region2D(); //Empty constructor
	Region2D(std::vector<std::vector<RGPAnnotatedHalfSegment2D>> listOfRegions);
	Region2D(std::string listOfRegion2DString);
	Region2D(std::ifstream& file); // Send in file for constructor (possibly .txt)
	~Region2D();

	// Methods
	std::string getRegionString();                          // Get the region as human readable ASCII string
	Number area();
	static bool isEmptyRegion(Region2D region);
	static bool isValidRegion(Region2D region);
	int getNumberOfFaces();
	std::vector<RGPSegment2D> getBoundingBox();
	bool operator==(const Region2D &p2d);
	bool operator!=(const Region2D &p2d);
	std::vector<RGPSegment2D> getCycle(int index);
	std::vector<RGPAnnotatedHalfSegment2D> getFace(int index);
	bool addFace(std::vector<RGPSegment2D>);
	bool update(int index, std::vector<RGPSegment2D>);	// Updates a whole region at specified index
	bool remove(int index);	                                // Removes a region at specified index
	std::vector<RGPSegment2D> operator[](int index);	// Retrieves a region at specified index

private:
	class Region2DImpl;

	// Fields
	Region2DImpl *impl;
};

#endif // REGION2D_H
