#include "../include/Point2D.h"

struct Point2DImplStruct {};

Point2D::Point2D() {}

Point2D::Point2D(std::vector<RGPPoint2D> listOfPoints) {}

Point2D::Point2D(std::ifstream& file) {}

Point2D::Point2D(std::string listOfPoint2DString) {}

Point2D::~Point2D() {}


std::string getPointString() {}  // Get the point as human readable ASCII string

// static
bool Point2D::isValidPoint() {}

bool Point2D::operator==(const Point2D &p2d) {}

bool Point2D::operator!=(const Point2D &p2d) {}

int Point2D::getNumberPoints() {}

std::vector<RGPSegment2D> Point2D::getBoundingBox() {}

bool Point2D::add(RGPPoint2D rgpp2d) {}

template <class T> bool Point2D::update(T it, RGPPoint2D rgpp2d) {}

template <class T> bool Point2D::remove(T it) {}
