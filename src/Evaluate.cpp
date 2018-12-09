#include "Evaluate.h"
#include "PredicateEnum.h"

Evaluate::Evaluate() {}

Evaluate::~Evaluate() {}

// ------------ Validate -----------------

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_shared, poi_disjoint};

	switch(predicate)
	{
	case DISJOINT:
		return !leftFeature[poi_shared] && leftFeature[poi_disjoint];
	case OVERLAP:
		return leftFeature[poi_shared] && leftFeature[poi_disjoint] && rightFeature[poi_disjoint];
	case CONTAINS:
		return leftFeature[poi_shared] && leftFeature[poi_disjoint] && !rightFeature[poi_disjoint];
	case EQUAL:
		return !leftFeature[poi_disjoint] && !rightFeature[poi_disjoint];
	case INSIDE:
		return !leftFeature[poi_disjoint] && rightFeature[poi_disjoint];
	default:
		return false;
	}
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

	switch(predicate)
	{
	case DISJOINT:
		return !leftFeature[poi_on_interior] && !leftFeature[poi_on_bound];
	case MEET:
		return !leftFeature[poi_on_interior] && leftFeature[poi_on_bound];
	case OVERLAP:
		return leftFeature[poi_on_interior] && leftFeature[poi_disjoint];
	case INSIDE:
		return leftFeature[poi_on_interior] && !leftFeature[poi_disjoint];
	default:
		return false;
	}
}

bool Evaluate::validate( Point2DImpl  &spatialObj_F, Region2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_inside, poi_on_bound, poi_outside};

	switch(predicate)
	{
	case DISJOINT:
		return !leftFeature[poi_inside] && !leftFeature[poi_on_bound];
	case MEET:
		return !leftFeature[poi_inside] && leftFeature[poi_on_bound];
	case OVERLAP:
		return leftFeature[poi_inside] && leftFeature[poi_outside];
	case INSIDE:
		return leftFeature[poi_inside] && !leftFeature[poi_outside];
	default:
		return false;
	}
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Line2DImpl    &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

	switch(predicate)
	{
	case DISJOINT:
		return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
				!rightFeature[bound_on_interior] &&
				leftFeature[seg_unshared] &&
				!leftFeature[bound_on_interior] &&
				!leftFeature[bound_shared];
	case MEET:
		return !(leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && leftFeature[seg_unshared];
	case OVERLAP:
		return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) && rightFeature[seg_unshared];
	case COVERS:
		return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
				leftFeature[seg_unshared] &&
				!leftFeature[bound_on_interior] &&
				leftFeature[bound_shared] &&
				!rightFeature[seg_unshared];
	case CONTAINS:
		return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
				leftFeature[seg_unshared] &&
				!leftFeature[bound_on_interior] &&
				!leftFeature[bound_shared] &&
				!rightFeature[seg_unshared];
	case EQUAL:
		return !rightFeature[bound_on_interior] &&
				!leftFeature[seg_unshared] &&
				!leftFeature[bound_on_interior] &&
				!leftFeature[bound_disjoint] &&
				!rightFeature[seg_unshared];
	case INSIDE:
		return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
				!rightFeature[bound_on_interior] &&
				!leftFeature[seg_unshared] &&
				!leftFeature[bound_shared] &&
				!leftFeature[bound_disjoint] &&
				rightFeature[seg_unshared];
	case COVEREDBY:
		return (leftFeature[seg_shared] || leftFeature[interior_poi_shared]) &&
				!rightFeature[bound_on_interior] &&
				!leftFeature[seg_unshared] &&
				leftFeature[bound_shared] &&
				!leftFeature[bound_disjoint] &&
				rightFeature[seg_unshared];
	default:
		return false;
	}
}

bool Evaluate::validate( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

	switch(predicate)
	{
	case DISJOINT:
		return !leftFeature[seg_inside] &&
				!(leftFeature[seg_shared] || leftFeature[poi_shared]) &&
				leftFeature[seg_outside] &&
				!leftFeature[bound_inside] &&
				!leftFeature[bound_shared];
	case MEET:
		return !leftFeature[seg_inside] &&
				!leftFeature[seg_outside] &&
				!leftFeature[bound_inside];
	case OVERLAP:
		return leftFeature[seg_inside] && leftFeature[seg_outside];
	case INSIDE:
		return leftFeature[seg_inside] &&
				!leftFeature[seg_outside] &&
				!leftFeature[bound_shared];
	case COVEREDBY:
		return leftFeature[seg_inside] &&
				!leftFeature[seg_outside] &&
				leftFeature[bound_shared];
	default:
		return false;
	}
}

bool Evaluate::validate( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG, Predicate predicate)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

	switch(predicate)
	{
	case DISJOINT:
		return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				!(rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
				(leftFeature[zero_one] || leftFeature[one_zero]) &&
				(rightFeature[zero_one] || rightFeature[one_zero]);
	case MEET:
		return !(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				!(rightFeature[one_two] || rightFeature[two_one]) &&
				(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[one_two] || leftFeature[two_one]) &&
				(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]);
	case OVERLAP:
		return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
	case COVERS:
		return (leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_two] || leftFeature[two_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[one_two] || leftFeature[two_one]) &&
				(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
				!(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]) &&
				!(rightFeature[zero_one] || rightFeature[one_zero]);
	case CONTAINS:
		return (rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[one_two] || leftFeature[two_one]) &&
				!(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
				(leftFeature[zero_one] || leftFeature[one_zero]) &&
				!(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
	case EQUAL:
		return !(rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[one_two] || leftFeature[two_one]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero]) &&
				!(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
	case INSIDE:
		return !(rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				(leftFeature[one_two] || leftFeature[two_one]) &&
				!(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero]);
	case COVEREDBY:
		return !(rightFeature[one_two] || rightFeature[two_one]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero] || leftFeature[one_one] || rightFeature[one_two] || rightFeature[two_one]) &&
				(leftFeature[zero_two] || leftFeature[two_zero] || leftFeature[one_one] || leftFeature[bound_poi_shared]) &&
				!(leftFeature[zero_one] || leftFeature[one_zero]) &&
				(leftFeature[one_two] || leftFeature[two_one] || leftFeature[one_one] || rightFeature[zero_one] || rightFeature[one_zero]);
	default:
		return false;
	}
}

// ------------ Determine -----------------

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Point2DImpl   &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_shared, poi_disjoint};

	if ( featureVectorF[poi_disjoint] ) { // A0B-
		if ( featureVectorF[poi_shared] ) { // A0B0, moved right
			if ( featureVectorG[poi_disjoint] ) { // A-B0
				return Predicate::OVERLAP; // 5
			} else {
				return Predicate::CONTAINS; // 4
			}
		} else {
			return Predicate::DISJOINT; // 1
		}
	} else { // A-B0, moved left
		if ( featureVectorG[poi_disjoint] ) { // vg[poi_disjoint]
			return Predicate::INSIDE; // 3
		} else {
			return Predicate::EQUAL; // 2
		}

	}
}

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_disjoint, poi_on_interior, poi_on_bound, bound_poi_disjoint};

	if( featureVectorF[poi_on_interior] ) { // A0B0
		if( featureVectorF[poi_on_bound] ) { // A0&B (boundary B) 
			if( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::OVERLAP; // 14
				} else {
					return Predicate::OVERLAP; //13
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::INSIDE; // 12
				} else {
					return Predicate::INSIDE; // 11
				}
			}
		} else {
			if (  featureVectorF[poi_disjoint]) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::OVERLAP; // 9
				} else {
					return Predicate::OVERLAP; // 10
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::INSIDE; // 7
				} else {
					return Predicate::INSIDE; // 8
				}
			}
		}
	} else {
		if( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_disjoint] ) { // A0B-
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::MEET; // 6
				} else {
					return Predicate::MEET; // 5
				}
			} else {
				if ( featureVectorG[bound_poi_disjoint] ) { // A-&B
					return Predicate::MEET; // 4
				} else {
					return Predicate::MEET; // 3
				}
			}
		} else { // A-&B
			if ( featureVectorG[bound_poi_disjoint] ) {
				return Predicate::DISJOINT; // 2
			} else {
				return Predicate::DISJOINT; // 1
			}
		}
	}
}

Predicate Evaluate::determine( Point2DImpl  &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF)
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {poi_inside, poi_on_bound, poi_outside};
	
	if ( featureVectorF[poi_inside] ) { // A0B0
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { // A0B-
				return Predicate::OVERLAP; // 7
			} else {
				return Predicate::INSIDE; // 6
			}
		} else {
			if ( featureVectorF[poi_outside] ) { // A0B-
				return Predicate::INSIDE; // 4
			} else {
				return Predicate::OVERLAP; // 5
			}
		}
	} else {
		if ( featureVectorF[poi_on_bound] ) { // A0&B
			if ( featureVectorF[poi_outside] ) { //A0B-
				return Predicate::MEET; // 3
			} else {
				return Predicate::MEET; // 2
			}
		} else {
			return Predicate::DISJOINT; // 1
		}
	}
}

Predicate Evaluate::determine( Line2DImpl   &spatialObj_F, Line2DImpl &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {seg_unshared, bound_on_interior, bound_disjoint, seg_shared, interior_poi_shared, bound_shared};

	if (featureVectorF[bound_shared])
	{
		if (featureVectorG[bound_on_interior])
		{
			if (featureVectorF[bound_on_interior])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_unshared])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::EQUAL;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::INSIDE;
							}
							else
							{
								return Predicate::INSIDE;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::DISJOINT;
							}
							else
							{
								return Predicate::DISJOINT;
							}
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::CONTAINS;
							}
							else
							{
								if (featureVectorG[bound_disjoint])
								{
									return Predicate::OVERLAP;
								}
								else
								{
									return Predicate::OVERLAP;
								}
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::DISJOINT;
						}
						else
						{
							return Predicate::DISJOINT;
						}
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::CONTAINS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
			}
			else
			{
				if (featureVectorG[bound_disjoint])
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::INSIDE;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::INSIDE;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[bound_disjoint])
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::CONTAINS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::CONTAINS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorG[bound_on_interior])
		{
			if (featureVectorF[bound_on_interior])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_unshared])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::EQUAL;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::COVEREDBY;
							}
							else
							{
								return Predicate::COVEREDBY;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::MEET;
							}
							else
							{
								return Predicate::MEET;
							}
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::COVERS;
							}
							else
							{
								if (featureVectorG[bound_disjoint])
								{
									return Predicate::OVERLAP;
								}
								else
								{
									return Predicate::OVERLAP;
								}
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::COVERS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
			}
			else
			{
				if (featureVectorG[bound_disjoint])
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::COVEREDBY;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorF[seg_unshared])
						{
							return Predicate::COVEREDBY;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[bound_disjoint])
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::COVERS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[interior_poi_shared])
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
				}
				else
				{
					if (featureVectorF[bound_on_interior])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::COVERS;
						}
						else
						{
							if (featureVectorG[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
					else
					{
						if (featureVectorG[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
	}
}

Predicate Evaluate::determine( Line2DImpl   &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {seg_unshared, seg_inside, seg_shared, seg_outside, poi_shared, bound_inside, bound_shared, bound_disjoint};

	if (featureVectorF[bound_shared])
	{
		if (featureVectorF[bound_inside])
		{
			if (featureVectorF[seg_inside])
			{
				if (featureVectorF[bound_disjoint])
				{
					if (featureVectorF[seg_outside])
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
					else
					{
						if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
						{
							return Predicate::DISJOINT;
						}
						else
						{
							if (featureVectorG[seg_unshared])
							{
								return Predicate::MEET;
							}
							else
							{
								return Predicate::MEET;
							}
						}
					}
				}
				else
				{
					if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
					{
						return Predicate::DISJOINT;
					}
					else
					{
						if (featureVectorG[seg_unshared])
						{
							return Predicate::MEET;
						}
						else
						{
							return Predicate::MEET;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::INSIDE;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
				else
				{
					if (featureVectorG[seg_unshared])
					{
						if (featureVectorF[seg_outside])
						{
							return Predicate::INSIDE;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
					else
					{
						if (featureVectorF[seg_outside])
						{
							return Predicate::INSIDE;
						}
						else
						{
							if (featureVectorF[bound_disjoint])
							{
								return Predicate::OVERLAP;
							}
							else
							{
								return Predicate::OVERLAP;
							}
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::INSIDE;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
			else
			{
				if (featureVectorG[seg_unshared])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::INSIDE;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::INSIDE;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorF[seg_shared] || featureVectorF[poi_shared])
		{
			if (featureVectorF[bound_inside])
			{
				if (featureVectorF[seg_inside])
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::MEET;
					}
					else
					{
						return Predicate::MEET;
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::COVEREDBY;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::COVEREDBY;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
		}
		else
		{
			if (featureVectorF[seg_inside])
			{
				if (featureVectorF[seg_outside])
				{
					return Predicate::MEET;
				}
				else
				{
					if (featureVectorF[bound_disjoint])
					{
						return Predicate::MEET;
					}
					else
					{
						return Predicate::MEET;
					}
				}
			}
			else
			{
				if (featureVectorF[bound_inside])
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::COVEREDBY;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
				else
				{
					if (featureVectorF[seg_outside])
					{
						return Predicate::COVEREDBY;
					}
					else
					{
						if (featureVectorF[bound_disjoint])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
	}
}

Predicate Evaluate::determine( Region2DImpl &spatialObj_F, Region2DImpl  &spatialObj_G, std::vector<bool> &featureVectorF, std::vector<bool> &featureVectorG )
{
	// Indicates what index in the bool vector represents what flag
	enum VectorFlag {zero_one, one_zero, one_two, two_one, zero_two, two_zero, one_one, bound_poi_shared};

	if (featureVectorG[one_two] || featureVectorG[two_one])
	{
		if (featureVectorF[zero_one] || featureVectorF[one_zero])
		{
			if (featureVectorF[zero_one] || featureVectorF[one_zero] || featureVectorF[one_one] || featureVectorG[one_two] || featureVectorG[two_one])
			{
				if (featureVectorF[one_two] || featureVectorF[two_one])
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::EQUAL;
					}
					else
					{
						return Predicate::COVEREDBY;
					}
				}
				else
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
					{
						return Predicate::INSIDE;
					}
					else
					{
						if (featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::COVEREDBY;
						}
						else
						{
							return Predicate::COVEREDBY;
						}
					}
				}
			}
			else
			{
				if (featureVectorF[one_two] || featureVectorF[two_one])
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
					{
						return Predicate::MEET;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
		}
		else
		{
			if (featureVectorG[zero_one] || featureVectorG[one_zero])
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
				{
					return Predicate::MEET;
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one])
					{
						if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::COVERS;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_two] || featureVectorF[two_one] || featureVectorG[one_two] || featureVectorG[two_one])
				{
					if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
					{
						return Predicate::DISJOINT;
					}
					else
					{
						return Predicate::MEET;
					}
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
	}
	else
	{
		if (featureVectorF[one_two] || featureVectorF[two_one])
		{
			if (featureVectorF[zero_one] || featureVectorF[one_zero])
			{
				if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
				{
					return Predicate::COVERS;
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::CONTAINS;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
				else
				{
					if (featureVectorF[one_two] || featureVectorF[two_one] || featureVectorF[one_one] || featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::COVERS;
					}
					else
					{
						if (featureVectorG[zero_one] || featureVectorG[one_zero])
						{
							return Predicate::OVERLAP;
						}
						else
						{
							return Predicate::OVERLAP;
						}
					}
				}
			}
		}
		else
		{
			if (featureVectorF[zero_two] || featureVectorF[two_zero] || featureVectorF[one_one] || featureVectorF[bound_poi_shared])
			{
				if (featureVectorF[zero_one] || featureVectorF[one_zero])
				{
					return Predicate::OVERLAP;
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
			else
			{
				if (featureVectorF[zero_one] || featureVectorF[one_zero])
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
				else
				{
					if (featureVectorG[zero_one] || featureVectorG[one_zero])
					{
						return Predicate::OVERLAP;
					}
					else
					{
						return Predicate::OVERLAP;
					}
				}
			}
		}
	}
}
