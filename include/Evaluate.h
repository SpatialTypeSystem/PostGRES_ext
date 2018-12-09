#ifndef EVALUATE_H
#define EVALUATE_H

#include "Point2DImpl.h"
#include "PredicateEnum.h"
#include "Line2DImpl.h"
#include "Region2DImpl.h"
#include <vector>

class Evaluate {
public:
    Evaluate();
    ~Evaluate();

// std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG
    static bool validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);
    static bool validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate);

    static Predicate determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static Predicate determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );

private:
	std::vector<std::vector<int> >* IM;
};

#endif //EVALUATE_H
