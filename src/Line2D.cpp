#include "../include/Line2D.h"

struct Line2DImplStruct {};

Line2D::Line2D() {}

Line2D::Line2D(std::vector<RGPSegment2D> listOfSegments) {}

Line2D::Line2D(std::string listOfLine2DString) {}

Line2D::Line2D(std::ifstream& file) {} // Send in file for constructor

Line2D::~Line2D() {}


// Methods
std::string Line2D::getLineString() {} // Get the line as human readable ASCII string

// static
bool Line2D::isValidPoint() {}

int Line2D::Line2D::getNumberPoints() {}

std::vector<RGPSegment2D> Line2D::getBoundingBox() {}

bool Line2D::add(RGPSegment2D rgp2d) {}

template <class T> bool Line2D::remove(T it) {}

template <class T> bool update(T it, RGPSegment2D rgps2d) {}

bool Line2D::operator==(const Line2D &l2d) {}

bool Line2D::operator!=(const Line2D &l2d) {}
