#include "Relationship2D.h"
#include "PlaneSweep.h"
#include "Explore.h"
#include "Evaluate.h"

#include <vector>

// =============================================================================
// --------------------------- Determination -----------------------------------
// =============================================================================

PREDICATE determine(Point2D &leftOperand, Point2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}
 
PREDICATE determine(Point2D &leftOperand, Line2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}
  
PREDICATE determine(Point2D &leftOperand, Region2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

PREDICATE determine(Line2D &leftOperand, Line2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

PREDICATE determine(Line2D &leftOperand, Region2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}
 
PREDICATE determine(Region2D &leftOperand, Region2D &rightOperand)
{
  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return determine(leftOperand, rightOperand, leftFeature, rightFeature);
}

// =============================================================================
// --------------------------- Verification ------------------------------------
// =============================================================================

// Disjoint
bool Relationship2D::disjoint(Point2D &leftOperand, Point2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !leftFeature[poi_shared] && leftFeature[poi_disjoint]; */
}

bool Relationship2D::disjoint(Point2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !leftFeature[poi_on_interior] && !leftFeature[poi_on_bound]; */
}

bool Relationship2D::disjoint(Point2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

  std::vector<bool> leftFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !leftFeature[poi_inside] && !leftFeature[poi_on_bound]; */
}

bool Relationship2D::disjoint(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
      !rightFeature[bound_on_interior] &&
      leftFeature[seg_unshared] &&
      !leftFeature[bound_on_interior] &&
      !leftFeature[bound_shared]; */
}

bool Relationship2D::disjoint(Line2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !leftFeature[seg_inside] &&
      !(leftFeature[seg_shared] || leftFeature[poi_shared]) &&
      leftFeature[seg_outside] &&
      !leftFeature[bound_inside] &&
      !leftFeature[bound_shared]; */
}

bool Relationship2D::disjoint(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, disjoint);

  /* return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      !(rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      (leftFeature[zero_one] || leftFeature[one_zero]) &&
      (rightFeature[zero_one] || rightFeature[one_zero]); */
}

// Meet
bool Relationship2D::meet(Point2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, meet);

  /* return !leftFeature[poi_on_interior] && leftFeature[poi_on_bound]; */
}

bool Relationship2D::meet(Point2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

  std::vector<bool> leftFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, meet);

  /* return !leftFeature[poi_inside] && leftFeature[poi_on_bound]; */
}

bool Relationship2D::meet(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, meet);

  /* return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && leftFeature[seg_unshared]; */
}

bool Relationship2D::meet(Line2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, meet);

  /* return !leftFeature[seg_inside] &&
      !leftFeature[seg_outside] &&
      !leftFeature[bound_inside]; */
}

bool Relationship2D::meet(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, meet);

  /* return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      !(rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[one_two] || leftFeature[two_one]) &&
      (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]); */
}

// Overlap
bool Relationship2D::overlap(Point2D &leftOperand, Point2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return leftFeature[poi_shared] && leftFeature[poi_disjoint] && rightFeature[poi_disjoint]; */
}

bool Relationship2D::overlap(Point2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return leftFeature[poi_on_interior] && leftFeature[poi_disjoint]; */
}

bool Relationship2D::overlap(Point2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

  std::vector<bool> leftFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return leftFeature[poi_inside] && leftFeature[poi_outside]; */
}

bool Relationship2D::overlap(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && rightFeature[seg_unshared]; */
}

bool Relationship2D::overlap(Line2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return leftFeature[seg_inside] &&
      leftFeature[seg_outside]; */
}

bool Relationship2D::overlap(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, overlap);

  /* return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]); */
}

// Equal
bool Relationship2D::equal(Point2D &leftOperand, Point2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, equal);

  /* return !leftFeature[poi_disjoint] && !rightFeature[poi_disjoint]; */
}

bool Relationship2D::equal(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, equal);

  /* return !rightFeature[bound_on_interior] &&
      !leftFeature[seg_unshared] &&
      !leftFeature[bound_on_interior] &&
      !leftFeature[bound_disjoint] &&
      !rightFeature[seg_unshared]; */
}

bool Relationship2D::equal(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, equal);

  /* return !(rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[one_two] || leftFeature[two_one]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero]) &&
      !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]); */
}

// Inside
bool Relationship2D::inside(Point2D &leftOperand, Point2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return !leftFeature[poi_disjoint] && rightFeature[poi_disjoint]; */
}

bool Relationship2D::inside(Point2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

  std::vector<bool> leftFeature(3, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return leftFeature[poi_on_interior] && !leftFeature[poi_disjoint]; */
}

bool Relationship2D::inside(Point2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

  std::vector<bool> leftFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return leftFeature[poi_inside] && !leftFeature[poi_outside]; */
}

bool Relationship2D::inside(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
      !rightFeature[bound_on_interior] &&
      !leftFeature[seg_unshared] &&
      !leftFeature[bound_shared] &&
      !leftFeature[bound_disjoint] &&
      rightFeature[seg_unshared]; */
}

bool Relationship2D::inside(Line2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return leftFeature[seg_inside] &&
      !leftFeature[seg_outside] &&
      !leftFeature[bound_shared]; */
}

bool Relationship2D::inside(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, inside);

  /* return !(rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[one_two] || leftFeature[two_one]) &&
      !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero]); */
}

// Contains
bool Relationship2D::contains(Point2D &leftOperand, Point2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {poi_shared, poi_disjoint};

  std::vector<bool> leftFeature(2, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, contains);

  /* return leftFeature[poi_shared] && leftFeature[poi_disjoint] && !rightFeature[poi_disjoint]; */
}

bool Relationship2D::contains(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, contains);

  /* return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
      leftFeature[seg_unshared] &&
      !leftFeature[bound_on_interior] &&
      !leftFeature[bound_shared] &&
      !rightFeature[seg_unshared];
      */
}

bool Relationship2D::contains(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  validate(leftOperand, rightOperand, leftFeature, rightFeature, contains);

  /* return (rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[one_two] || leftFeature[two_one]) &&
      !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      (leftFeature[zero_one] || leftFeature[one_zero]) &&
      !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
      */
}

// Covers
bool Relationship2D::covers(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, covers);

  /* return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
      leftFeature[seg_unshared] &&
      !leftFeature[bound_on_interior] &&
      leftFeature[bound_shared] &&
      !rightFeature[seg_unshared];
      */
}

bool Relationship2D::covers(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, covers);

  /* return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[one_two] || leftFeature[two_one]) &&
      (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      !(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]) &&
      !(rightFeature[zero_one] || rightFeature[one_zero]);
      */
}

// CoveredBy
bool Relationship2D::coveredBy(Line2D &leftOperand, Line2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

  std::vector<bool> leftFeature(6, false);
  std::vector<bool> rightFeature(3, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, coveredBy);

  /* return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
      !rightFeature[bound_on_interior] &&
      !leftFeature[seg_unshared] &&
      leftFeature[bound_shared] &&
      !leftFeature[bound_disjoint] &&
      rightFeature[seg_unshared];
      */
}

bool Relationship2D::coveredBy(Line2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

  std::vector<bool> leftFeature(7, false);
  std::vector<bool> rightFeature(1, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, coveredBy);

  /* return leftFeature[seg_inside] &&
      !leftFeature[seg_outside] &&
      leftFeature[bound_shared];
      */
}

bool Relationship2D::coveredBy(Region2D &leftOperand, Region2D &rightOperand)
{
  // Indicates what index in the bool vector represents what flag
  enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

  std::vector<bool> leftFeature(8, false);
  std::vector<bool> rightFeature(4, false);

  // Explore
  explore(leftOperand, rightOperand, leftFeature, rightFeature);
  // Evaluate
  return validate(leftOperand, rightOperand, leftFeature, rightFeature, coveredBy);

  /* return !(rightFeature[one_two] || rightFeature[two_one]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
      (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
      !(leftFeature[zero_one] || leftFeature[one_zero]) &&
      (leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
      */
}
