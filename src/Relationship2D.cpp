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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::disjoint);

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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::disjoint);

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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::disjoint);

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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::disjoint);

  // return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
  //     !rightFeature[bound_on_interior] &&
  //     leftFeature[seg_unshared] &&
  //     !leftFeature[bound_on_interior] &&
  //     !leftFeature[bound_shared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::disjoint);

  // return !leftFeature[seg_inside] &&
  //     !(leftFeature[seg_shared] || leftFeature[poi_shared]) &&
  //     leftFeature[seg_outside] &&
  //     !leftFeature[bound_inside] &&
  //     !leftFeature[bound_shared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::disjoint);

  // return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
  //     (leftFeature[zero_one] || leftFeature[one_zero]) &&
  //     (rightFeature[zero_one] || rightFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::meet);

  // return !leftFeature[poi_on_interior] && leftFeature[poi_on_bound];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::meet);

  // return !leftFeature[poi_inside] && leftFeature[poi_on_bound];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::meet);

  // return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && leftFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::meet);

  // return !leftFeature[seg_inside] &&
  //     !leftFeature[seg_outside] &&
  //     !leftFeature[bound_inside];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::meet);

  // return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(rightFeature[one_two] || rightFeature[two_one]) &&
  //     (leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one]) &&
  //     (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::overlap);

  // return leftFeature[poi_shared] && leftFeature[poi_disjoint] && rightFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::overlap);

  // return leftFeature[poi_on_interior] && leftFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::overlap);

  // return leftFeature[poi_inside] && leftFeature[poi_outside];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::overlap);

  // return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::overlap);

  // return leftFeature[seg_inside] &&
  //     leftFeature[seg_outside];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::overlap);

  // return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     (leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     (leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::equal);

  // return !leftFeature[poi_disjoint] && !rightFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::equal);

  // return !rightFeature[bound_on_interior] &&
  //     !leftFeature[seg_unshared] &&
  //     !leftFeature[bound_on_interior] &&
  //     !leftFeature[bound_disjoint] &&
  //     !rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::equal);

  // return !(rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one]) &&
  //     !(leftFeature[zero_one] || leftFeature[one_zero]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::inside);

  // return !leftFeature[poi_disjoint] && rightFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::inside);

  // return leftFeature[poi_on_interior] && !leftFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, Predicate::inside);

  // return leftFeature[poi_inside] && !leftFeature[poi_outside];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::inside);

  // return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
  //     !rightFeature[bound_on_interior] &&
  //     !leftFeature[seg_unshared] &&
  //     !leftFeature[bound_shared] &&
  //     !leftFeature[bound_disjoint] &&
  //     rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::inside);

  // return leftFeature[seg_inside] &&
  //     !leftFeature[seg_outside] &&
  //     !leftFeature[bound_shared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::inside);

  // return !(rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     (leftFeature[one_two] || leftFeature[two_one]) &&
  //     !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
  //     !(leftFeature[zero_one] || leftFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::contains);

  // return leftFeature[poi_shared] && leftFeature[poi_disjoint] && !rightFeature[poi_disjoint];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::contains);

  // return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
  //     leftFeature[seg_unshared] &&
  //     !leftFeature[bound_on_interior] &&
  //     !leftFeature[bound_shared] &&
  //     !rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::contains);

  // return (rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one]) &&
  //     !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
  //     (leftFeature[zero_one] || leftFeature[one_zero]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::covers);

  // return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
  //     leftFeature[seg_unshared] &&
  //     !leftFeature[bound_on_interior] &&
  //     leftFeature[bound_shared] &&
  //     !rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::covers);

  // return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one]) &&
  //     (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
  //     !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]) &&
  //     !(rightFeature[zero_one] || rightFeature[one_zero]);
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::coveredBy);

  // return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
  //     !rightFeature[bound_on_interior] &&
  //     !leftFeature[seg_unshared] &&
  //     leftFeature[bound_shared] &&
  //     !leftFeature[bound_disjoint] &&
  //     rightFeature[seg_unshared];
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::coveredBy);

  /* return leftFeature[seg_inside] &&
      !leftFeature[seg_outside] &&
      leftFeature[bound_shared]; */
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
  return Evaluate::validate(leftOperand, rightOperand, leftFeature, rightFeature, Predicate::coveredBy);

  /* return !(rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero]) &&
      (leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]); */
}
