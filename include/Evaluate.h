#ifndef EVALUATE_H
#define EVALUATE_H

#include "Point2DImpl.h"
#include "PredicateEnum.h"
#include "Line2DImpl.h"
#include "Region2DImpl.h"
#include <vector>

// Evaluate class
// This class takes in the spatial object references and determines or validates
// a spatial relationship. To do this, we either use the binary tree method with
// hardcoded if statements or we use thinned matrix boolean expressions.

// This file is NOT for public use or distribution.
// This is only for engineer use.

class Evaluate {
public:
    Evaluate();
    ~Evaluate();

    static bool validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, Predicate predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);

    static Predicate determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF);
    static Predicate determine( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );

private:
	std::vector<std::vector<int> >* IM;
};

#endif //EVALUATE_H
