#include "Relationship2D.h"
#include "PlaneSweep.h"

#include <vector>

bool Relationship2D::disjoint(Point2D &leftOperand, Point2D &rightOperand)
{
//    PlaneSweep ps;
//    std::vector<bool> rightFeature(1, false);
//    std::vector<bool> leftFeature(1, false);
//    ps.explore(leftOperand, rightOperand, leftFeature, rightFeature);

}

bool Relationship2D::disjoint(Point2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::disjoint(Point2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::disjoint(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::disjoint(Line2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::disjoint(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::meet(Point2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::meet(Point2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::meet(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::meet(Line2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::meet(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::overlap(Point2D &leftOperand, Point2D &rightOperand)
{

}

bool Relationship2D::overlap(Point2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::overlap(Point2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::overlap(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::overlap(Line2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::overlap(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::equal(Point2D &leftOperand, Point2D &rightOperand)
{

}

bool Relationship2D::equal(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::equal(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::inside(Point2D &leftOperand, Point2D &rightOperand)
{

}

bool Relationship2D::inside(Point2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::inside(Point2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::inside(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::inside(Line2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::inside(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::contains(Point2D &leftOperand, Point2D &rightOperand)
{

}

bool Relationship2D::contains(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::contains(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::covers(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::covers(Region2D &leftOperand, Region2D &rightOperand)
{

}


bool Relationship2D::coveredBy(Line2D &leftOperand, Line2D &rightOperand)
{

}

bool Relationship2D::coveredBy(Line2D &leftOperand, Region2D &rightOperand)
{

}

bool Relationship2D::coveredBy(Region2D &leftOperand, Region2D &rightOperand)
{

}
