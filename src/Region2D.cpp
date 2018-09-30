#include "../include/Region2D.h"

struct Region2DImplStruct {};

Region2D::Region2D() {}

Region2D::Region2D(std::vector<std::vector<RGPSegment2D>> listOfRegions) {}

Region2D::Region2D(std::string listOfRegion2DString) {}

Region2D::Region2D(std::ifstream& file) {}

Region2D::~Region2D() {}


std::string Region2D::getRegionString() {} // Get the region as human readable ASCII string

Number Region2D::area() {}

// static
bool Region2D::isValidRegion(Region2D region) {}

int Region2D::getNumberOfFaces() {}

std::vector<RGPSegment2D> Region2D::getBoundingBox() {}

bool Region2D::addFace(std::vector<RGPSegment2D>) {}

template <class T> bool Region2D::update(T it, std::vector<RGPSegment2D>) {}

template <class T> bool Region2D::remove(T it) {}

bool Region2D::operator==(const Region2D &p2d) {}

bool Region2D::operator!=(const Region2D &p2d) {}
