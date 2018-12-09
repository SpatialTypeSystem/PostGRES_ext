#include "PredicateEnum.h"
#include "Relationship2D.h"
#include "PlaneSweep.h"
#include "Explore.h"
#include "Evaluate.h"

#include <vector>

// =============================================================================
// --------------------------- Determination -----------------------------------
// =============================================================================

Predicate Relationship2D::determine(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

Predicate Relationship2D::determine(Point2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

Predicate Relationship2D::determine(Point2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature);
}

Predicate Relationship2D::determine(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

Predicate Relationship2D::determine(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

Predicate Relationship2D::determine(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

// =============================================================================
// --------------------------- Verification ------------------------------------
// =============================================================================

// Disjoint
bool Relationship2D::disjoint(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::DISJOINT);

  // return !leftFeature[poi_shared] && leftFeature[poi_disjoint];
}

bool Relationship2D::disjoint(Point2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::DISJOINT);

  // return !leftFeature[poi_on_interior] && !leftFeature[poi_on_bound];
}

bool Relationship2D::disjoint(Point2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::DISJOINT);

  // return !leftFeature[poi_inside] && !leftFeature[poi_on_bound];
}

bool Relationship2D::disjoint(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::DISJOINT);
}

bool Relationship2D::disjoint(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::DISJOINT);
}

bool Relationship2D::disjoint(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::DISJOINT);
}

// Meet
bool Relationship2D::meet(Point2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::MEET);
}

bool Relationship2D::meet(Point2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::MEET);
}

bool Relationship2D::meet(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::MEET);
}

bool Relationship2D::meet(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::MEET);
}

bool Relationship2D::meet(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::MEET);
}

// Overlap
bool Relationship2D::overlap(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::OVERLAP);
}

bool Relationship2D::overlap(Point2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::OVERLAP);
}

bool Relationship2D::overlap(Point2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::OVERLAP);
}

bool Relationship2D::overlap(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::OVERLAP);
}

bool Relationship2D::overlap(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::OVERLAP);
}

bool Relationship2D::overlap(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::OVERLAP);
}

// Equal
bool Relationship2D::equal(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::EQUAL);
}

bool Relationship2D::equal(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::EQUAL);
}

bool Relationship2D::equal(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::EQUAL);
}

// Inside
bool Relationship2D::inside(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::INSIDE);
}

bool Relationship2D::inside(Point2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::INSIDE);
}

bool Relationship2D::inside(Point2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::INSIDE);
}

bool Relationship2D::inside(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::INSIDE);
}

bool Relationship2D::inside(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::INSIDE);
}

bool Relationship2D::inside(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::INSIDE);
}

// Contains
bool Relationship2D::contains(Point2D &leftOperand, Point2D &rightOperand)
{
  // Conversion to programmer data type
  Point2DForProgrammer leftFP = Point2DForProgrammer(leftOperand);
  Point2DForProgrammer rightFP = Point2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPPoint2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPPoint2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::CONTAINS);
}

bool Relationship2D::contains(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::CONTAINS);
}

bool Relationship2D::contains(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::CONTAINS);
}

// Covers
bool Relationship2D::covers(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::COVERS);
}

bool Relationship2D::covers(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::COVERS);
}

// CoveredBy
bool Relationship2D::coveredBy(Line2D &leftOperand, Line2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Line2DForProgrammer rightFP = Line2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::COVEREDBY);
}

bool Relationship2D::coveredBy(Line2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Line2DForProgrammer leftFP = Line2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::COVEREDBY);
}

bool Relationship2D::coveredBy(Region2D &leftOperand, Region2D &rightOperand)
{
  // Conversion to programmer data type
  Region2DForProgrammer leftFP = Region2DForProgrammer(leftOperand);
  Region2DForProgrammer rightFP = Region2DForProgrammer(rightOperand);

  // Retrieve iterators from objects
  std::vector<RGPAnnotatedHalfSegment2D>::iterator leftIterator = leftFP.iterator();
  std::vector<RGPAnnotatedHalfSegment2D>::iterator rightIterator = rightFP.iterator();

  // Topological feature vectors
  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);


  // Explore
  Explore::explore(leftIterator, rightIterator, leftFeature, rightFeature);
  // Evaluate
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::COVEREDBY);
}
