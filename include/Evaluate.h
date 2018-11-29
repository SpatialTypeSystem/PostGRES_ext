#ifndef EVALUATE_H
#define EVALUATE_H

#include "Point2DImpl.h"
#include "Line2DImpl.h"
#include "Region2DImpl.h"
#include <vector>

enum PREDICATE { disjoint, meet, overlap, covers, contains, equal, inside, coveredBy };

class Evaluate {
public:
    Evaluate();
    ~Evaluate();

// std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG
    static bool validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);
    static bool validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);
    static bool validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);
    static bool validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, PREDICATE predicate);

    static PREDICATE determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static PREDICATE determine( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static PREDICATE determine( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static PREDICATE determine( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static PREDICATE determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );
    static PREDICATE determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG );

private:
	std::vector<std::vector<int> >* IM;
};

#endif //EVALUATE_H
