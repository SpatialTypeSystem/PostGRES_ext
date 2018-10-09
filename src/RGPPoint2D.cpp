#include "../include/RGPPoint2D.h"

// Constructors

RGPPoint2D::RGPPoint2D(Number x, Number y)
{
    this->x = x;
    this->y = y;
}
RGPPoint2D::~RGPPoint2D() {}

// Methods

// All comparing operators will be based off lexicographical ordering.
bool RGPPoint2D::operator==(const RGPPoint2D& rhs) {
    return (this->x == rhs.x) && (this->y == rhs.y);
}
bool RGPPoint2D::operator!=(const RGPPoint2D &rhs) {
    return (this->x != rhs.x) && (this->y != rhs.y);
}
bool RGPPoint2D::operator<(const RGPPoint2D &rhs) {
    if (this->x < rhs.x) {
        return true;
    } else if (this->x == rhs.x && this->y < rhs.y) {
        return true;
    } else {
        return false;
    }
}
bool RGPPoint2D::operator<=(const RGPPoint2D &rhs) {
    return (*this<rhs) || (*this==rhs);
}
bool RGPPoint2D::operator>(const RGPPoint2D &rhs) {
    return !(*this<=rhs);
}
bool RGPPoint2D::operator>=(const RGPPoint2D &rhs) {
    return (*this>rhs) || (*this==rhs);
}

//std::ostream& operator<<(std::ostream& os, const RGPPoint2D &p) {
//    os << p.x << "," << p.y;
//    return os;
//}
//
//std::istream& operator>>(std::istream& is, RGPPoint2D &p) {
//    std::string x = "";
//    std::string y = "";
//
//    // Read the two values
//    getline(is, x, ',');
//    is >> y;
//
//    // Convert strings to Number and assign to RGPPoint2D
//    p.x = Number(x);
//    p.y = Number(y);
//
//    return is;
//}