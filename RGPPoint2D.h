#ifndef RGPPOINT2D_H
#define RGPPOINT2D_H

#include "Number.h"

struct RGPPoint2D {

    // Members

    Number x, y;

    // Constructors

    RGPPoint2D(Number x, Number y);
    ~RGPPoint2D();

    // Methods

    bool operator==(const RGPPoint2D &rhs);
    bool operator!=(const RGPPoint2D &rhs);
    bool operator<(const RGPPoint2D &rhs);
    bool operator<=(const RGPPoint2D &rhs);
    bool operator>(const RGPPoint2D &rhs);
    bool operator>=(const RGPPoint2D &rhs);

};

#endif //RGPPOINT2D_H
