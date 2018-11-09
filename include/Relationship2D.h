#ifndef POSTGRES_EXT_RELATIONSHIP2D_H
#define POSTGRES_EXT_RELATIONSHIP2D_H

#include "Point2D.h"
#include "Line2D.h"
#include "Region2D.h"

class Relationship2D {

public:

  Relationship2D();
  ~Relationship2D();

  // Disjoint
  static bool disjoint(Point2D &leftOperand, Point2D &rightOperand);
  static bool disjoint(Point2D &leftOperand, Line2D &rightOperand);
  static bool disjoint(Point2D &leftOperand, Region2D &rightOperand);
  static bool disjoint(Line2D &leftOperand, Line2D &rightOperand);
  static bool disjoint(Line2D &leftOperand, Region2D &rightOperand);
  static bool disjoint(Region2D &leftOperand, Region2D &rightOperand);

  // Meet
  static bool meet(Point2D &leftOperand, Line2D &rightOperand);
  static bool meet(Point2D &leftOperand, Region2D &rightOperand);
  static bool meet(Line2D &leftOperand, Line2D &rightOperand);
  static bool meet(Line2D &leftOperand, Region2D &rightOperand);
  static bool meet(Region2D &leftOperand, Region2D &rightOperand);

  // Overlap
  static bool overlap(Point2D &leftOperand, Point2D &rightOperand);
  static bool overlap(Point2D &leftOperand, Line2D &rightOperand);
  static bool overlap(Point2D &leftOperand, Region2D &rightOperand);
  static bool overlap(Line2D &leftOperand, Line2D &rightOperand);
  static bool overlap(Line2D &leftOperand, Region2D &rightOperand);
  static bool overlap(Region2D &leftOperand, Region2D &rightOperand);

  // Equal
  static bool equal(Point2D &leftOperand, Point2D &rightOperand);
  static bool equal(Line2D &leftOperand, Line2D &rightOperand);
  static bool equal(Region2D &leftOperand, Region2D &rightOperand);

  // Inside
  static bool inside(Point2D &leftOperand, Point2D &rightOperand);
  static bool inside(Point2D &leftOperand, Line2D &rightOperand);
  static bool inside(Point2D &leftOperand, Region2D &rightOperand);
  static bool inside(Line2D &leftOperand, Line2D &rightOperand);
  static bool inside(Line2D &leftOperand, Region2D &rightOperand);
  static bool inside(Region2D &leftOperand, Region2D &rightOperand);

  // Contains
  static bool contains(Point2D &leftOperand, Point2D &rightOperand);
  static bool contains(Line2D &leftOperand, Line2D &rightOperand);
  static bool contains(Region2D &leftOperand, Region2D &rightOperand);

  // Covers
  static bool covers(Line2D &leftOperand, Line2D &rightOperand);
  static bool covers(Region2D &leftOperand, Region2D &rightOperand);

  // Covered by
  static bool coveredBy(Line2D &leftOperand, Line2D &rightOperand);
  static bool coveredBy(Line2D &leftOperand, Region2D &rightOperand);
  static bool coveredBy(Region2D &leftOperand, Region2D &rightOperand);
};

#endif //POSTGRES_EXT_RELATIONSHIP2D_H
