#ifndef POSTGRES_EXT_RELATIONSHIP2D_H
#define POSTGRES_EXT_RELATIONSHIP2D_H

#include "PredicateEnum.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Region2D.h"

// Relationship2D class
// Contains all spatial relationship calls for end user to call.
// By including this file, all users will be able to access and operate
// the spatial engine of our software.
// This file will be publicly distributed.

class Relationship2D {

public:

  Relationship2D();
  ~Relationship2D();

  // Determine relationship - these will return a predicate enum telling us
  // what the relationship is between the two objects passed in
  static Predicate determine(Point2D &leftOperand, Point2D &rightOperand);
  static Predicate determine(Point2D &leftOperand, Line2D &rightOperand);
  static Predicate determine(Point2D &leftOperand, Region2D &rightOperand);
  static Predicate determine(Line2D &leftOperand, Line2D &rightOperand);
  static Predicate determine(Line2D &leftOperand, Region2D &rightOperand);
  static Predicate determine(Region2D &leftOperand, Region2D &rightOperand);

  // Disjoint - returns a bool indicating if two objects have disjoint relationship
  static bool disjoint(Point2D &leftOperand, Point2D &rightOperand);
  static bool disjoint(Point2D &leftOperand, Line2D &rightOperand);
  static bool disjoint(Point2D &leftOperand, Region2D &rightOperand);
  static bool disjoint(Line2D &leftOperand, Line2D &rightOperand);
  static bool disjoint(Line2D &leftOperand, Region2D &rightOperand);
  static bool disjoint(Region2D &leftOperand, Region2D &rightOperand);

  // Meet - returns a bool indicating if two objects have meet relationship
  static bool meet(Point2D &leftOperand, Line2D &rightOperand);
  static bool meet(Point2D &leftOperand, Region2D &rightOperand);
  static bool meet(Line2D &leftOperand, Line2D &rightOperand);
  static bool meet(Line2D &leftOperand, Region2D &rightOperand);
  static bool meet(Region2D &leftOperand, Region2D &rightOperand);

  // Overlap - returns a bool indicating if two objects have overlap relationship
  static bool overlap(Point2D &leftOperand, Point2D &rightOperand);
  static bool overlap(Point2D &leftOperand, Line2D &rightOperand);
  static bool overlap(Point2D &leftOperand, Region2D &rightOperand);
  static bool overlap(Line2D &leftOperand, Line2D &rightOperand);
  static bool overlap(Line2D &leftOperand, Region2D &rightOperand);
  static bool overlap(Region2D &leftOperand, Region2D &rightOperand);

  // Equal - returns a bool indicating if two objects have equal relationship
  static bool equal(Point2D &leftOperand, Point2D &rightOperand);
  static bool equal(Line2D &leftOperand, Line2D &rightOperand);
  static bool equal(Region2D &leftOperand, Region2D &rightOperand);

  // Inside - returns a bool indicating if two objects have inside relationship
  static bool inside(Point2D &leftOperand, Point2D &rightOperand);
  static bool inside(Point2D &leftOperand, Line2D &rightOperand);
  static bool inside(Point2D &leftOperand, Region2D &rightOperand);
  static bool inside(Line2D &leftOperand, Line2D &rightOperand);
  static bool inside(Line2D &leftOperand, Region2D &rightOperand);
  static bool inside(Region2D &leftOperand, Region2D &rightOperand);

  // Contains - returns a bool indicating if two objects have contains relationship
  static bool contains(Point2D &leftOperand, Point2D &rightOperand);
  static bool contains(Line2D &leftOperand, Line2D &rightOperand);
  static bool contains(Region2D &leftOperand, Region2D &rightOperand);

  // Covers - returns a bool indicating if two objects have covers relationship
  static bool covers(Line2D &leftOperand, Line2D &rightOperand);
  static bool covers(Region2D &leftOperand, Region2D &rightOperand);

  // Covered by - returns a bool indicating if two objects have covered by relationship
  static bool coveredBy(Line2D &leftOperand, Line2D &rightOperand);
  static bool coveredBy(Line2D &leftOperand, Region2D &rightOperand);
  static bool coveredBy(Region2D &leftOperand, Region2D &rightOperand);
};

#endif //POSTGRES_EXT_RELATIONSHIP2D_H
